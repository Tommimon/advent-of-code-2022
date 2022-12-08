REQUIRED_SPACE = 30000000
TOTAL_SAPCE = 70000000


def execute(input: list) -> (int, int):
    result1 = 0
    fileSystem = {}
    currDir = ''
    currPath = ''
    for i, cmd in enumerate(input):
        if '$ ls' in cmd:
            j = i + 1
            while '$' not in input[j] and j < len(input) - 1:
                if 'dir ' in input[j]:
                    fileSystem[currPath + (currDir if currPath == '' or currPath == '/' else ('/' + currDir))][3] += 1
                j += 1
        elif '$ cd ..' in cmd:
            currDir = '/' if currPath == '/' else (list(filter("".__ne__, currPath.split('/')))[-1])
            currPath = ('/' + '/'.join(
                map(str, list(filter("".__ne__, currPath.split('/')))[:-1]))) if currPath != '/' else ''
        elif '$ cd' in cmd:
            if cmd.split()[2] == '/':
                fileSystem['/'] = (['/', '', 0, 0])
                currDir = '/'
                currPath = ''
                continue
            currPath += currDir if currPath == '' or currPath == '/' else '/' + currDir
            currDir = cmd.split()[2]
            fileSystem[currPath + (currDir if currPath == '' or currPath == '/' else ('/' + currDir))] = (
                [cmd.split()[2], currPath, 0, 0])
        elif 'dir ' in cmd:
            ...
        else:
            fileSystem[currPath + (currDir if currPath == '' or currPath == '/' else ('/' + currDir))][2] += int(
                cmd.split()[0])

    while True:
        change = False
        for k in fileSystem.keys():
            if fileSystem[k][3] == 0 and fileSystem[k][1] != '':
                change = True
                fileSystem[fileSystem[k][1]][2] += fileSystem[k][2]
                fileSystem[fileSystem[k][1]][3] -= 1
                fileSystem[k][3] = 1
                break
        if not change:
            break

    size = []
    for k in fileSystem.keys():
        size.append(fileSystem[k][2])
        if fileSystem[k][2] < 100000:
            result1 += fileSystem[k][2]

    neededSpace = REQUIRED_SPACE - (TOTAL_SAPCE - fileSystem['/'][2])
    result2 = 0
    for s in sorted(size):
        if s > neededSpace:
            result2 = s
            break
    return result1, result2


with open('input.txt') as f:
    lines = f.readlines()
    cleanLines = []
    for line in lines:
        cleanLines.append(line.strip())
res1, res2 = execute(cleanLines)
print(f'DAY07_1 RESULT: {res1}')
print(f'DAY07_2 RESULT: {res2}')
