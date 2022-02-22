from datetime import datetime
import mysql.connector
import pytz
import re
import requests
from xml.etree import ElementTree

from scripts.dbconfig import DB_HOST, DB_USER, DB_PASSWORD


xml_namespaces = {'atom': 'http://www.w3.org/2005/Atom'}

comment_feed_url = 'https://smugmug.com/hack/feed.mg?Type=usercomments&Data=cmubuggy&format=atom10'
photo_feed_url = 'https://smugmug.com/hack/feed.mg?Type=nicknameRecent&Data=cmubuggy&format=atom10'


# pip install mysql-connector-python
# pip3 install mysql-connector-python-rf
# Run with 'python3 -m scripts.fetch_smugmug_activity'
def main():
    config = {
        'user': DB_USER,
        'password': DB_PASSWORD,
        'host': DB_HOST,
        'database': 'cmubuggy',
        'raise_on_warnings': True
    }

    cnx = mysql.connector.connect(**config)

    try:
        (comment_id, comment_created_at) = get_most_recent_comment_id(cnx)
        new_comments = fetch_new_comments(comment_feed_url, 'comment_id', comment_created_at)
        insert_comments(cnx, new_comments)
    except Exception as e:
        print(e)
    finally:
        cnx.close()

    return
    try:
        recent_photos = fetch_recent_photos(photo_feed_url)
        _print_items(recent_photos)
    except Exception as e:
        print(e)
    finally:
        cnx.close()

    # TODO: Insert into database any new records
    # TODO: Schedule with Crontab - https://towardsdatascience.com/how-to-schedule-python-scripts-with-cron-the-only-guide-youll-ever-need-deea2df63b4e
    # TODO: Figure out where to route errors


def get_most_recent_comment_id(connection):
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

    return None


def fetch_new_comments(url, last_comment_id, last_comment_created_at):
    response = requests.get(url)
    xml_root = ElementTree.fromstring(response.content)

    new_comments = []
    for entry in _get_entries_from_xml_root(xml_root):
        try:
            comment = parse_comment_from_entry(entry)

            # Stop if we have found the most recently cached comment, or if we have
            # progressed before it in time (in case the comment is deleted on SmugMug)
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

    # TODO: Stop SQL injection
    cursor.executemany(query, new_comments)
    connection.commit()
    cursor.close()


def fetch_recent_photos(url):
    response = requests.get(url)
    xml_root = ElementTree.fromstring(response.content)

    recent_photos = []
    for entry in _get_entries_from_xml_root(xml_root):
        try:
            photo = parse_photo_addition_from_entry(entry)
            recent_photos.append(photo)
        except Exception as e:
            print(e)

    return recent_photos


def parse_photo_addition_from_entry(entry):
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


def _get_entries_from_xml_root(xml_root):
    return xml_root.findall('atom:entry', xml_namespaces)


def _get_item_from_element(el, tag):
    return el.find('atom:%s' % tag, xml_namespaces)


def _get_utc_datetime_from_timestamp(timestamp):
    # We get timestamps in form '2021-10-17T18:28:03-07:00' with timezone specified as '[+/-]##:##',
    # but strptime expects timezone specified as '[+/-]####', so we strip the last three characters
    # off and tack the '00' back on.
    timestamp = timestamp[:-3] + '00'
    datetime_in_utc = datetime.strptime(timestamp, '%Y-%m-%dT%H:%M:%S%z').astimezone(pytz.UTC)
    return datetime_in_utc.replace(tzinfo=None)


def _print_items(items):
    for item in items:
        for k, v in item.items():
            print('%s: %s' % (k, v))
        print('\n')


if __name__ == "__main__":
    main()