from argparse import ArgumentParser
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


# Pre-requisites:
#     sudo pip install mysql-connector-python
#     sudo pip3 install mysql-connector-python-rf
#
# Run with:
#     python3 -m scripts.fetch_smugmug_activity [--initialize]
#
# Scheduling:
# This script was scheduled using Crontab as the root user. Prior to scheduling,
# the mysql-connector-python packages had to be installed for root. Script output
# can be found in /var/mail/root.
#     sudo su
#     sudo pip install mysql-connector-python
#     sudo pip3 install mysql-connector-python-rf
#     crontab -e

# The following expression was used for scheduling:
#     0 * * * * /usr/bin/python3 /var/www/cmubuggy.org/scripts/fetch_smugmug_activity.py
#
# Other notes:
#   The `updated` timestamp in an entry is not the time the item was created, but
#   rather the last time it was last modified in the SmugMug UI. This causes entropy
#   in the results that can make it hard to tell when to stop searching through the
#   results, so during normal running mode we use the current time as a proxy for
#   `created_at`. While not exact, we run the script once an hour, so it is close
#   enough to the actual created at time.
#
#   When running this script for the first time, pass the --initialize flag to use
#   the dynamic but reasonably accurate `updated` timestamp from entries instead, so
#   that the results make some sense to a user viewing an activity feed.
#
def main():
    parser = ArgumentParser()
    parser.add_argument('--initialize', action='store_true')
    args = parser.parse_args()

    global INITIALIZE_MODE
    INITIALIZE_MODE = args.initialize

    connection = open_db_connection()

    try:
        new_comments = fetch_new_comments()
        insert_comments(connection, new_comments)
    except Exception as e:
        print(e)

    try:
        recent_photos = fetch_recent_photos()
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


def fetch_new_comments():
    # The SmugMug comment feed does not paginate, so hopefully we never receive more
    # than 100 comments in an hour. Or perhaps it is an infinite feed. I guess we will
    # find out when we have more than 100 comments total :)
    response = requests.get(COMMENT_FEED_URL)
    xml_root = ElementTree.fromstring(response.content)

    new_comments = []
    for entry in _get_entries_from_xml_root(xml_root):
        try:
            comment = parse_comment_from_entry(entry)
            new_comments.append(comment)

        except Exception as e:
            print(e)

    # Comments are read in reverse chronologically, so reverse the order
    new_comments.reverse()
    return new_comments


def parse_comment_from_entry(entry):
    comment = {}

    smugmug_id = _get_item_from_element(entry, 'id').text
    matches = re.search(r'\Asmugmug:comment:(?P<comment_id>\d+)\Z', smugmug_id)
    comment['comment_id'] = matches.group('comment_id')

    comment['comment_url'] = _get_item_from_element(entry, 'link').get('href')

    title = _get_item_from_element(entry, 'title').text
    matches = re.search(r'\A(?P<author>.*) commented on (.*) photo\Z', title)
    comment['author'] = matches.group('author')

    content = _get_item_from_element(entry, 'content').text
    matches = re.search(
        r'<img src="(?P<thumbnail_url>https:\/\/[^"]+\.[\w]+)".*>.*<p>Comment: (?P<comment>.*)<\/p>',
        content)
    if matches != None:
        comment['thumbnail_url'] = matches.group('thumbnail_url')
        comment['comment'] = matches.group('comment')

    if INITIALIZE_MODE:
        timestamp = _get_item_from_element(entry, 'updated').text
        comment['created_at'] = _get_utc_datetime_from_timestamp(timestamp)
    else:
        comment['created_at'] = datetime.utcnow()

    return comment


def insert_comments(connection, new_comments):
    if not new_comments:
        return

    cursor = connection.cursor()
    query = '''
        insert into smugmug_comments (
            comment_id,
            comment_url,
            thumbnail_url,
            author,
            comment,
            created_at
        )
        values (
            %(comment_id)s,
            %(comment_url)s,
            %(thumbnail_url)s,
            %(author)s,
            %(comment)s,
            %(created_at)s
        )
        on duplicate key update
            comment_url = values(comment_url),
            thumbnail_url = values(thumbnail_url),
            author = values(author),
            comment = values(comment)
        '''
    cursor.executemany(query, new_comments)
    connection.commit()
    cursor.close()


def fetch_recent_photos():
    url = PHOTO_FEED_URL
    recent_photos = []
    seen_photos = set()

    while True:
        response = requests.get(url)
        xml_root = ElementTree.fromstring(response.content)

        entries = _get_entries_from_xml_root(xml_root)
        if not entries:
            break

        for entry in entries:
            try:
                photo = parse_photo_upload_from_entry(entry)

                # SmugMug's pagination isn't perfect, so filter out duplicate entries
                photo_identifier = (photo['gallery_slug'], photo['photo_id'])
                if photo_identifier not in seen_photos:
                    recent_photos.append(photo)
                    seen_photos.add(photo_identifier)

            except Exception as e:
                print(e)

        url = _get_next_url_from_xml_root(xml_root)

    # Photos are read in reverse chronologically, so reverse the order
    recent_photos.reverse()
    return recent_photos


def parse_photo_upload_from_entry(entry):
    photo = {}

    content_url = _get_item_from_element(entry, 'link').get('href')
    matches = re.search(
        r'^(?P<gallery_url>https:\/\/cmubuggy.smugmug.com\/(?P<folder_slug>.+))\/(?P<gallery_slug>[^\/]+)\/(?P<photo_id>[^\/]+)(\/*)$',
        content_url)

    photo['content_url'] = content_url
    photo['gallery_url'] = matches.group('gallery_url')
    photo['gallery_slug'] = \
        '%s/%s' % (matches.group('gallery_slug'), matches.group('gallery_slug'))
    photo['gallery_name'] = matches.group('gallery_slug').replace('-', ' ')
    photo['photo_id'] = matches.group('photo_id')

    photo['thumbnail_url'] = _get_item_from_element(entry, 'id').text

    if INITIALIZE_MODE:
        timestamp = _get_item_from_element(entry, 'updated').text
        photo['created_at'] = _get_utc_datetime_from_timestamp(timestamp)
    else:
        photo['created_at'] = datetime.utcnow()

    return photo


def insert_photos(connection, new_photos):
    if not new_photos:
        return

    cursor = connection.cursor()
    query = '''
        insert into smugmug_uploads (
            gallery_url,
            content_url,
            thumbnail_url,
            gallery_name,
            gallery_slug,
            photo_id,
            created_at
        )
        values (
            %(gallery_url)s,
            %(content_url)s,
            %(thumbnail_url)s,
            %(gallery_name)s,
            %(gallery_slug)s,
            %(photo_id)s,
            %(created_at)s
        )
        on duplicate key update
            gallery_url = values(gallery_url),
            content_url = values(content_url),
            thumbnail_url = values(thumbnail_url),
            gallery_name = values(gallery_name),
            gallery_slug = values(gallery_slug)
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
    # We get timestamps in form '2021-10-17T18:28:03-07:00' with timezone specified
    # as '[+/-]##:##', but strptime expects timezone specified as '[+/-]####', so
    # we strip the last three characters off and tack the '00' back on.
    timestamp = timestamp[:-3] + '00'
    as_datetime = datetime.strptime(timestamp, '%Y-%m-%dT%H:%M:%S%z')
    return as_datetime.astimezone(pytz.UTC).replace(tzinfo=None)


if __name__ == "__main__":
    main()