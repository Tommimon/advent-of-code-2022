import requests
import datetime
import time

COOKIE_FILE = 'cookies'
URL = 'https://adventofcode.com/{}/day/{}/input'
USER = 'Tommimon'

time.sleep(20)

year = datetime.date.today().year
day = datetime.date.today().day

with open(COOKIE_FILE, "r") as cookies_file:
    cookies = cookies_file.readlines()[0]
headers = {"Cookie": cookies}

folder = str(day) if day >= 10 else '0'+str(day)
puzzle_input = requests.get(URL.format(year, day), headers=headers).text

path = USER + '/d' + folder + '/input'
with open(path, "w") as file:
    file.write(puzzle_input)
