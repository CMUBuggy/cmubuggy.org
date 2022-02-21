from datetime import datetime
import mysql.connector
import re
import requests
from xml.etree import ElementTree

xml_namespaces = {'atom': 'http://www.w3.org/2005/Atom'}

comment_feed_url = 'https://smugmug.com/hack/feed.mg?Type=usercomments&Data=cmubuggy&format=atom10'
photo_feed_url = 'https://smugmug.com/hack/feed.mg?Type=nicknameRecent&Data=cmubuggy&format=atom10'


# Run with 'python3 -m scripts.fetch_smugmug_activity'
def main():


    config = {
        'user': 'cmubuggy',
        'password': '',
        'host': '127.0.0.1',
        'database': 'cmubuggy',
        'raise_on_warnings': True
    }

    cnx = mysql.connector.connect(**config)

    print('connected!')

    cnx.close()

    try:
        recent_comments = fetch_recent_comments(comment_feed_url)
        _print_items(recent_comments)
    except Exception as e:
        print(e)

    try:
        recent_photos = fetch_recent_photos(photo_feed_url)
        _print_items(recent_photos)
    except Exception as e:
        print(e)

    # TODO: Insert into database any new records
    # TODO: Schedule with Crontab - https://towardsdatascience.com/how-to-schedule-python-scripts-with-cron-the-only-guide-youll-ever-need-deea2df63b4e
    # TODO: Figure out where to route errors


def fetch_recent_comments(url):
    response = requests.get(url)
    xml_root = ElementTree.fromstring(response.content)

    recent_comments = []
    for entry in _get_entries_from_xml_root(xml_root):
        try:
            comment = parse_comment_from_entry(entry)
            recent_comments.append(comment)
        except Exception as e:
            print(e)

    return recent_comments

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
    comment['created_at'] = _get_datetime_from_timestamp(_get_item_from_element(entry, 'updated').text)

    return comment


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
    photo['created_at'] = _get_datetime_from_timestamp(_get_item_from_element(entry, 'updated').text)

    return photo


def _get_entries_from_xml_root(xml_root):
    return xml_root.findall('atom:entry', xml_namespaces)


def _get_item_from_element(el, tag):
    return el.find('atom:%s' % tag, xml_namespaces)


def _get_datetime_from_timestamp(timestamp):
    # We get timestamps in form '2021-10-17T18:28:03-07:00' with timezone specified as '[+/-]##:##',
    # but strptime expects timezone specified as '[+/-]####', so we strip the last three characters
    # off and tack the '00' back on.
    timestamp = timestamp[:-3] + '00'
    return datetime.strptime(timestamp, '%Y-%m-%dT%H:%M:%S%z')


def _print_items(items):
    for item in items:
        for k, v in item.items():
            print('%s: %s' % (k, v))
        print('\n')


if __name__ == "__main__":
    main()