import pathlib
import platform
import os
import stat
import re

# First part: setup pre-commit hook
text = '''#!/bin/sh
# update leaderboard before commit
python3 leaderboard.py
git add README.md
'''

if platform.system() == 'Windows':
    text = text.replace('python3', 'python')

path = pathlib.Path('.git/hooks/pre-commit')
fp = open(path, 'w')
fp.write(text)
fp.close()

if platform.system() != 'Windows':
    st = os.stat(path)
    os.chmod(path, st.st_mode | stat.S_IEXEC)


# Second part: write cookies to file if needed
COOKIE_FILE = 'cookies'

cookies = "empty"
wrong = False
while not (re.match("session=[a-z0-9]*", cookies) or cookies == ""):
    if wrong:
        print("This isn't a valid cookie please retry")
    wrong = True
    try:
        with open(COOKIE_FILE, "r") as input_file:
            current = input_file.readlines()[0]
            cookies = input("New cookies (press ENTER to keep current): ")
    except (IndexError, FileNotFoundError):
        cookies = input("Cookies not found, enter your session cookies: ")
    cookies = cookies.strip("Cookie: ")

if cookies != "":
    with open(COOKIE_FILE, 'w') as output_file:
        output_file.write(cookies)


print("Hooks setup finished!")
