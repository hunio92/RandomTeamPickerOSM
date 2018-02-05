from urllib.request import Request, urlopen
from bs4 import BeautifulSoup as soup
import sqlite3, time

# database = sqlite3.connect('database.db')

# cursor = database.cursor()
# cursor.execute('CREATE TABLE IF NOT EXISTS announcements(id	INTEGER PRIMARY KEY AUTOINCREMENT, link TEXT, img_link TEXT, price INTEGER, title TEXT, area TEXT, rooms INTEGER, surface TEXT, publishedBy TEXT, agency TEXT)')

url = 'https://en.onlinesoccermanager.com/LeagueTypes/';
req = Request(url, headers={'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'})
urlToScrap = urlopen(req).read()

page_html = urlToScrap

page_soup = soup(page_html, "lxml")

containers = page_soup.findAll("table", {"class":"thSortable"})

print(page_soup)
#
# cursor.close()
# database.close()
