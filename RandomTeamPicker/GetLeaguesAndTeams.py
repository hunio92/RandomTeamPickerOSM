from urllib.request import Request, urlopen
import json as simplejson
import sqlite3, time

database = sqlite3.connect('database.db')

# time.sleep(5)

cursor = database.cursor()
cursor.execute('DROP TABLE IF EXISTS leagues')
cursor.execute('DROP TABLE IF EXISTS teams')
cursor.execute('CREATE TABLE IF NOT EXISTS leagues(league_id INTEGER PRIMARY KEY, league_name TEXT, league_link TEXT)')
cursor.execute('CREATE TABLE IF NOT EXISTS teams(team_id INTEGER PRIMARY KEY AUTOINCREMENT, league_id INTEGER, team_name TEXT)')

headers = { 'User-Agent' : 'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_4; en-US) AppleWebKit/534.3 (KHTML, like Gecko) Chrome/6.0.472.63 Safari/534.3' }
url = 'https://web-api.onlinesoccermanager.com/api/v1/leagueTypes'
req = Request(url, None, headers)
page_content = urlopen(req)
parsed_content = page_content.read()
page_content.close()
jsonLeague = simplejson.loads(parsed_content.decode('utf-8'))
for i in range(len(jsonLeague)):
    cursor.execute('INSERT INTO leagues (league_id, league_name, league_link) VALUES (?, ?, ?)', (jsonLeague[i]['id'], jsonLeague[i]['name'], "https://us.onlinesoccermanager.com/LeagueTypes/League/" + str(jsonLeague[i]['id'])))
    url = 'https://web-api.onlinesoccermanager.com/api/v1/leagueTypes/' + str(jsonLeague[i]['id']) + '/teams'
    req = Request(url, None, headers)
    page_content = urlopen(req)
    parsed_content = page_content.read()
    page_content.close()
    jsonTeams = simplejson.loads(parsed_content.decode('utf-8'))
    for j in range(len(jsonTeams)):
        cursor.execute('INSERT INTO teams (league_id, team_name) VALUES (?, ?)', (jsonLeague[i]['id'], jsonTeams[j]['name']))
    database.commit()

cursor.close()
database.close()
