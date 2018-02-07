from urllib.request import Request, urlopen
import simplejson as json
import sqlite3

database = sqlite3.connect('C:\\Users\hunor.orban\Documents\RandomTeamPickerOSM\database.db')

cursor = database.cursor()
cursor.execute('DROP TABLE IF EXISTS leagues')
cursor.execute('CREATE TABLE IF NOT EXISTS leagues(id INTEGER PRIMARY KEY AUTOINCREMENT, league_name TEXT, league_id TEXT, league_link TEXT)')

headers = { 'User-Agent' : 'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_4; en-US) AppleWebKit/534.3 (KHTML, like Gecko) Chrome/6.0.472.63 Safari/534.3' }
url = 'https://web-api.onlinesoccermanager.com/api/v1/leagueTypes';
req = Request(url, None, headers)
page_content = urlopen(req)
parsed_content = page_content.read()
page_content.close()
jsonData = json.loads(parsed_content.decode('utf-8'))
for i in range(len(jsonData)):
    cursor.execute('INSERT INTO leagues (league_name, league_id, league_link) VALUES (?, ?, ?)', (jsonData[i]['name'], str(jsonData[i]['id']), "https://us.onlinesoccermanager.com/LeagueTypes/League/" + str(jsonData[i]['id'])))
    database.commit()
cursor.close()
database.close()
 
