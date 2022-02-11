from datetime import datetime
import re
from xml.dom.minidom import Element
import requests
from xml.etree import ElementTree

xml_namespaces = {'atom': 'http://www.w3.org/2005/Atom'}

comment_feed_url = 'https://smugmug.com/hack/feed.mg?Type=usercomments&Data=cmubuggy&format=atom10'
photo_feed_url = 'https://smugmug.com/hack/feed.mg?Type=nicknameRecent&Data=cmubuggy&format=atom10'


# Run with 'python3 -m scripts.fetch_smugmug_activity'
def main():
    try:
        recent_comments = fetch_recent_comments(comment_feed_url)
        _print_items(recent_comments)
    except:
        pass

    try:
        recent_photos = fetch_recent_photos(photo_feed_url)
        _print_items(recent_photos)
    except:
        pass

    # TODO: Insert into database any new records
    # TODO: Schedule with Crontab - https://towardsdatascience.com/how-to-schedule-python-scripts-with-cron-the-only-guide-youll-ever-need-deea2df63b4e
    # TODO: Figure out where to route errors


def fetch_recent_comments(url: str) -> 'list[dict]':
    response = requests.get(url)
    xml_root = ElementTree.fromstring(response.content)

    recent_comments = []
    for entry in _get_entries_from_xml_root(xml_root):
        comment = {}
        recent_comments.append(comment)

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

        comment['action_url'] = _get_item_from_element(entry, 'link').get('href')
        comment['created_at'] = datetime.fromisoformat(_get_item_from_element(entry, 'updated').text)

    return recent_comments


def fetch_recent_photos(url: str) -> 'list[dict]':
    response = requests.get(url)
    xml_root = ElementTree.fromstring(response.content)

    recent_photos = []
    for entry in _get_entries_from_xml_root(xml_root):
        photo = {}
        recent_photos.append(photo)

        action_url = _get_item_from_element(entry, 'link').get('href')
        matches = re.search(
            r'(?P<gallery_url>https:\/\/cmubuggy.smugmug.com\/(?P<gallery_slug>[^\/]+\/[^\/]+)\/)(?P<photo_slug>[^\/]+)\/*',
            action_url)
        matches_dict = matches.groupdict()

        photo['action_url'] = action_url
        photo['gallery_url'] = matches_dict['gallery_url']
        photo['gallery_slug'] = matches_dict['gallery_slug']
        photo['photo_slug'] = matches_dict['photo_slug']
        photo['thumbnail_url'] = _get_item_from_element(entry, 'id').text
        photo['created_at'] = datetime.fromisoformat(_get_item_from_element(entry, 'updated').text)

    return recent_photos


def _get_entries_from_xml_root(xml_root: Element) -> 'list[Element]':
    return xml_root.findall('atom:entry', xml_namespaces)


def _get_item_from_element(el: Element, tag: str):
    return el.find(f'atom:{tag}', xml_namespaces)


def _print_items(items: 'list[dict]'):
    for item in items:
        for k, v in item.items():
            print(f'{k}: {v}')
        print('\n')


if __name__ == "__main__":
    main()