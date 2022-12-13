import numpy as np


def execute1(input: list, st: list, en: list) -> int:
    input = np.array(input)
    s = [st[0], st[1], 0, 0]
    queue = [s]
    closed_list = [st[0], st[1]]
    while len(queue) != 0:
        s = queue.pop(0)
        if s[0] == en[0] and s[1] == en[1]:
            return s[3]
        height = ord(input[s[0]][s[1]]) if input[s[0]][s[1]] != 'S' else ord('a')
        if s[0] + 1 < input.shape[0] and (
                (input[s[0] + 1][s[1]] != 'E' and ord(input[s[0] + 1][s[1]]) <= height + 1) or (
                input[s[0] + 1][s[1]] == 'E' and ord('z') <= height + 1)):
            if [s[0] + 1, s[1]] not in closed_list:
                cost = h([s[0] + 1, s[1]], en) + s[2] + 1
                queue.append([s[0] + 1, s[1], cost, s[3] + 1])
                closed_list.append([s[0] + 1, s[1]])
        if s[0] - 1 >= 0 and ((input[s[0] - 1][s[1]] != 'E' and ord(input[s[0] - 1][s[1]]) <= height + 1) or (
                input[s[0] - 1][s[1]] == 'E' and ord('z') <= height + 1)):
            if [s[0] - 1, s[1]] not in closed_list:
                cost = h([s[0] - 1, s[1]], en) + s[2] + 1
                queue.append([s[0] - 1, s[1], cost, s[3] + 1])
                closed_list.append([s[0] - 1, s[1]])
        if s[1] + 1 < input.shape[1] and (
                (input[s[0]][s[1] + 1] != 'E' and ord(input[s[0]][s[1] + 1]) <= height + 1) or (
                input[s[0]][s[1] + 1] == 'E' and ord('z') <= height + 1)):
            if [s[0], s[1] + 1] not in closed_list:
                cost = h([s[0], s[1] + 1], en) + s[2] + 1
                queue.append([s[0], s[1] + 1, cost, s[3] + 1])
                closed_list.append([s[0], s[1] + 1])
        if s[1] - 1 >= 0 and ((input[s[0]][s[1] - 1] != 'E' and ord(input[s[0]][s[1] - 1]) <= height + 1) or (
                input[s[0]][s[1] - 1] == 'E' and ord('z') <= height + 1)):
            if [s[0], s[1] - 1] not in closed_list:
                cost = h([s[0], s[1] - 1], en) + s[2] + 1
                queue.append([s[0], s[1] - 1, cost, s[3] + 1])
                closed_list.append([s[0], s[1] - 1])
        queue.sort(key=costSort)
    return np.inf


def execute2(input: list, st: list, en: list) -> int:
    input[st[0]][st[1]] = 'a'
    input = np.array(input)
    min = np.inf
    for r in range(input.shape[0]):
        for c in range(input.shape[1]):
            if input[r][c] == 'a':
                tmp = execute1(list(input), [r, c], en)
                if tmp < min:
                    min = tmp
    return min


def h(s: list, en: list) -> int:
    return np.abs((en[0] - s[0])) + np.abs((en[1] - s[1]))


def costSort(val):
    return val[2]


with open('input.txt') as f:
    lines = f.readlines()
    map = []
    start = []
    end = []
    for line in lines:
        map.append([*line.strip()])
        if 'S' in map[len(map) - 1]:
            start = [len(map) - 1, map[len(map) - 1].index('S')]
        if 'E' in map[len(map) - 1]:
            end = [len(map) - 1, map[len(map) - 1].index('E')]

print(f'DAY12_1 RESULT: {execute1(map, start, end)}')
print(f'DAY12_2 RESULT: {execute2(map, start, end)}')
