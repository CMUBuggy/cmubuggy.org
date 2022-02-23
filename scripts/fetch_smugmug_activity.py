from datetime import datetime
from os.path import abspath, dirname, join

import json
import mysql.connector
import pytz
import re
import requests
from xml.etree import ElementTree


DB_CONFIG_FILE = 'dbconfig.json'

COMMENT_FEED_URL = 'https://smugmug.com/hack/feed.mg?Type=usercomments&Data=cmubuggy&format=atom10'
PHOTO_FEED_URL = 'https://smugmug.com/hack/feed.mg?Type=nicknameRecent&Data=cmubuggy&format=atom10'
XML_NAMESPACES = {'atom': 'http://www.w3.org/2005/Atom'}

# TODO: Schedule with Crontab - https://towardsdatascience.com/how-to-schedule-python-scripts-with-cron-the-only-guide-youll-ever-need-deea2df63b4e
# TODO: Figure out where to route errors


# pip install mysql-connector-python
# pip3 install mysql-connector-python-rf
# Run with 'python3 -m scripts.fetch_smugmug_activity'
def main():
    connection = open_db_connection()

    try:
        (comment_id, comment_created_at) = get_most_recent_comment(connection)
        new_comments = fetch_new_comments(comment_id, comment_created_at)
        insert_comments(connection, new_comments)
    except Exception as e:
        print(e)

    try:
        (gallery_slug, photo_slug, created_at) = get_most_recent_photo(connection)
        recent_photos = fetch_recent_photos(gallery_slug, photo_slug, created_at)
        insert_photos(connection, recent_photos)
    except Exception as e:
        print(e)

    connection.close()


def open_db_connection():
    root_directory = dirname(dirname(abspath(__file__)))
    f = open(join(root_directory, DB_CONFIG_FILE))
    config = json.load(f)
    f.close()

    return mysql.connector.connect(
        host=config['DB_HOST'],
        database=config['DB_NAME'],
        user=config['DB_USER'],
        password=config['DB_PASSWORD'],
        raise_on_warnings= True)


def get_most_recent_comment(connection):
    cursor = connection.cursor()
    query = '''
        select comment_id, created_at
        from smugmug_comments
        order by created_at desc
        limit 1
        '''

    cursor.execute(query)
    for (comment_id, created_at) in cursor:
        return (comment_id, created_at)

    return (None, datetime.min)


def fetch_new_comments(last_comment_id, last_comment_created_at):
    response = requests.get(COMMENT_FEED_URL)
    xml_root = ElementTree.fromstring(response.content)

    new_comments = []
    for entry in _get_entries_from_xml_root(xml_root):
        try:
            comment = parse_comment_from_entry(entry)

            # Stop if we have found the most recently cached comment, or if we have
            # progressed before it in time (in case the comment we are looking for
            # was deleted on SmugMug)
            if (comment['comment_id'] == last_comment_id  or
                comment['created_at'] <= last_comment_created_at):
                break

            new_comments.append(comment)

        except Exception as e:
            print(e)

    # TODO: Fetch more comments if we haven't found the most recent one
    # Comments are read in reverse chronologically, so reverse the order
    new_comments.reverse()
    return new_comments


def parse_comment_from_entry(entry):
    comment = {}

    smugmug_id = _get_item_from_element(entry, 'id').text
    matches = re.search(r'\Asmugmug:comment:(?P<comment_id>\d+)\Z', smugmug_id)
    comment['comment_id'] = matches.groupdict()['comment_id']

    title = _get_item_from_element(entry, 'title').text
    matches = re.search(r'\A(?P<author>.*) commented on (.*) photo\Z', title)
    comment['author'] = matches.groupdict()['author']

    content = _get_item_from_element(entry, 'content').text
    matches = re.search(
        r'<img src="(?P<thumbnail_url>https:\/\/[^"]+\.[\w]+)".*>.*<p>Comment: (?P<comment>.*)<\/p>',
        content)
    matches_dict = matches.groupdict()
    comment['thumbnail_url'] = matches_dict['thumbnail_url']
    comment['comment'] = matches_dict['comment']

    comment['comment_url'] = _get_item_from_element(entry, 'link').get('href')

    timestamp = _get_item_from_element(entry, 'updated').text
    comment['created_at'] = _get_utc_datetime_from_timestamp(timestamp)

    return comment


def insert_comments(connection, new_comments):
    cursor = connection.cursor()
    query = '''
        insert into smugmug_comments
            (comment_id, comment_url, thumbnail_url, author, comment, created_at)
        values
            (%(comment_id)s, %(comment_url)s, %(thumbnail_url)s, %(author)s, %(comment)s, %(created_at)s)
        '''
    cursor.executemany(query, new_comments)
    connection.commit()
    cursor.close()


def get_most_recent_photo(connection):
    cursor = connection.cursor()
    query = '''
        select gallery_slug, photo_slug, created_at
        from smugmug_uploads
        order by created_at desc
        limit 1
        '''

    cursor.execute(query)
    for (gallery_slug, photo_slug, created_at) in cursor:
        return (gallery_slug, photo_slug, created_at)

    return (None, None, datetime.min)


def fetch_recent_photos(last_gallery_slug, last_photo_slug, last_photo_uploaded_at):
    url = PHOTO_FEED_URL
    recent_photos = []
    seen_photos = set()

    found_last_photo = False
    while not found_last_photo:

        response = requests.get(url)
        xml_root = ElementTree.fromstring(response.content)

        entries = _get_entries_from_xml_root(xml_root)
        if not entries:
            break

        for entry in entries:
            try:
                photo = parse_photo_upload_from_entry(entry)

                # TODO: find a way to sort the feed?? - this is breaking the unique constraint right now :(
                # Stop if we have found the most recently cached photo, or if we have
                # progressed before it in time (in case the photo we are looking for
                # was deleted on SmugMug)
                if ((photo['gallery_slug'] == last_gallery_slug and
                     photo['photo_slug'] == last_photo_slug)):
                    found_last_photo = True
                    break

                photo_identifier = (photo['gallery_slug'], photo['photo_slug'])
                if photo_identifier not in seen_photos:
                    recent_photos.append(photo)
                    seen_photos.add(photo_identifier)
            except Exception as e:
                print(e)

        if not found_last_photo:
            url = _get_next_url_from_xml_root(xml_root)

    # Photos are read in reverse chronologically, so reverse the order
    recent_photos.reverse()
    return recent_photos


def parse_photo_upload_from_entry(entry):
    photo = {}

    content_url = _get_item_from_element(entry, 'link').get('href')
    matches = re.search(
        r'(?P<gallery_url>https:\/\/cmubuggy.smugmug.com\/(?P<gallery_slug>(?P<folder>[^\/]+)\/(?P<gallery>[^\/]+))\/)(?P<photo_slug>[^\/]+)\/*',
        content_url)
    matches_dict = matches.groupdict()

    photo['content_url'] = content_url
    photo['gallery_url'] = matches_dict['gallery_url']
    photo['gallery_slug'] = matches_dict['gallery_slug']
    photo['photo_slug'] = matches_dict['photo_slug']
    photo['gallery_name'] = '%s / %s' % (matches_dict['folder'], matches_dict['gallery'].replace('-', ' '))
    photo['thumbnail_url'] = _get_item_from_element(entry, 'id').text

    timestamp = _get_item_from_element(entry, 'updated').text
    photo['created_at'] = _get_utc_datetime_from_timestamp(timestamp)

    return photo


def insert_photos(connection, new_photos):
    cursor = connection.cursor()
    query = '''
        insert into smugmug_uploads
            (gallery_url, content_url, thumbnail_url, gallery_name, gallery_slug, photo_slug, created_at)
        values
            (%(gallery_url)s, %(content_url)s, %(thumbnail_url)s, %(gallery_name)s, %(gallery_slug)s, %(photo_slug)s, %(created_at)s)
        '''
    cursor.executemany(query, new_photos)
    connection.commit()
    cursor.close()


def _get_next_url_from_xml_root(xml_root):
    next_link = xml_root.find('atom:link[@rel="next"]', XML_NAMESPACES)
    return None if next_link == None else next_link.get('href')

def _get_entries_from_xml_root(xml_root):
    return xml_root.findall('atom:entry', XML_NAMESPACES)


def _get_item_from_element(el, tag):
    return el.find('atom:%s' % tag, XML_NAMESPACES)


def _get_utc_datetime_from_timestamp(timestamp):
    # We get timestamps in form '2021-10-17T18:28:03-07:00' with timezone specified as '[+/-]##:##',
    # but strptime expects timezone specified as '[+/-]####', so we strip the last three characters
    # off and tack the '00' back on.
    timestamp = timestamp[:-3] + '00'
    datetime_in_utc = datetime.strptime(timestamp, '%Y-%m-%dT%H:%M:%S%z').astimezone(pytz.UTC)
    return datetime_in_utc.replace(tzinfo=None)


if __name__ == "__main__":
    main()