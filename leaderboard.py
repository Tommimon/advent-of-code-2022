import time
import json
try:
    import requests
except ModuleNotFoundError:
    print("Can't find requests module, stopping update")
    exit(0)

YEAR = '2022'
URL = 'https://adventofcode.com/' + YEAR + '/leaderboard/private/view/976110.json'
COOKIE_FILE = 'cookies'
README_FILE = 'README.md'
DELTA_TIME = 900
MARKER_BEGIN = '<!---LEADERBOARD_GRID_BEGIN:'
MARKER_END = 'LEADERBOARD_GRID_END--->'


def update_leaderboard():
    ts = round(time.time())
    try:
        with open(README_FILE, "r", encoding="utf-8") as input_file:
            old_readme = input_file.read().split(MARKER_BEGIN)
        old_metadata = old_readme[1].split(MARKER_END)[0].split('\n')
        old_ts = int(old_metadata[0])
        user_metadata = old_metadata[1:]
        user_map = list(map(lambda u: tuple(u.split(',')), user_metadata))
    except (FileNotFoundError, ValueError, IndexError):
        print("Can't load old data")
        return False

    if ts < old_ts + DELTA_TIME:
        print("Not enough time elapsed since last update, skipping leaderboard update")
        return True

    print("Current leaderboard is too old, updating...")
    try:
        with open(COOKIE_FILE, "r") as input_file:
            cookies = input_file.readlines()[0]
        headers = {"Cookie": cookies}
        print("Cookies loaded successfully")
    except (FileNotFoundError, IndexError):
        print("Cookies not found")
        return False

    json_data = requests.get(URL, headers=headers).text
    if json_data.find('"owner_id":976110') == -1:  # check leaderboard
        print("An error occurred while downloading the new leaderboard")
        return False
    print("New leaderboard downloaded successfully")

    new_readme = old_readme[0] + MARKER_BEGIN + str(ts) + '\n' + '\n'.join(user_metadata) + MARKER_END
    try:
        new_readme += '\n' + write_grid(json.loads(json_data), user_map)
    except Exception:
        print("Malformed metadata")
        return False

    try:
        with open(README_FILE, 'w', encoding="utf-8") as output_file:
            output_file.write(new_readme)
    except (FileNotFoundError, PermissionError):
        print("Can't write new leaderboard to file")
        return False
    return True


def image_link(name, user_map):
    for u in user_map:
        if u[0] == name:
            if len(u) > 1:
                return u[1]
    return 'https://www.pngall.com/wp-content/uploads/5/User-Profile-PNG-Clipart.png'


def github_username(name, user_map):
    for u in user_map:
        if u[0] == name:
            if len(u) > 2:
                return u[2]
    return name.replace(' ', '')


def folder_name(name, user_map):
    for u in user_map:
        if u[0] == name:
            if len(u) > 3:
                return u[3]
    return github_username(name, user_map)


def stars(member, day):
    if str(day) in member["completion_day_level"].keys():
        if '2' in member["completion_day_level"][str(day)].keys():
            return '**'
        return '*'
    return ' '


def write_grid(data, user_map):
    users = list(map(lambda e: e[0], user_map))
    members = list(filter(lambda e: e["name"] in users, data["members"].values()))
    members.sort(key=lambda e: e["local_score"], reverse=True)
    text = '| |'
    for m in members:
        name = m["name"]
        text += ' <a href="https://github.com/{}"><img src="{}" width="40" height="40"/>' \
                '</a> |'.format(github_username(name, user_map), image_link(name, user_map))

    text += '\n| :---: |'
    for _m in members:
        text += ' :---: |'

    text += '\n| **Day** |'
    for m in members:
        name = m["name"]
        text += ' <a href="https://github.com/{}"><sup><sub>{}</sub></sup>' \
                '</a> |'.format(github_username(name, user_map), folder_name(name, user_map))

    for i in range(25):
        text += '\n| [{}][d{}] |'.format(i+1, i+1)
        for j, m in enumerate(members):
            text += ' [{}][d{}u{}] |'.format(stars(m, i+1), i+1, j)

    text += '\n| **Points** |'
    for m in members:
        text += ' {} |'.format(m["local_score"])

    text += '\n\n'
    for i in range(25):
        text += '\n[d{}]: https://adventofcode.com/{}/day/{}'.format(i+1, YEAR, i+1)

    text += '\n\n'
    for i in range(25):
        for j, m in enumerate(members):
            text += '\n[d{}u{}]: https://github.com/Tommimon/advent-of-code-{}/' \
                    'tree/main/{}/{}'.format(i+1, j, YEAR, folder_name(m["name"], user_map), "d" + str(i+1).zfill(2))
    return text


if not update_leaderboard():
    print("Couldn't update the leaderboard")
else:
    print("Leaderboard is up to date")
