import numpy as np


def execute1(input: list) -> int:
    res1 = 0
    tmp1 = 0
    for el in input:
        if el == '':
            if res1 < tmp1:
                res1 = tmp1
            tmp1 = 0
        else:
            tmp1 += int(el)
    return res1


def execute2(input: list) -> int:
    tmp = 0
    top3 = np.array([0, 0, 0])
    for el in input:
        if el == '':
            if top3[0] < tmp:
                top3[0] = tmp
                top3.sort()
            tmp = 0
        else:
            tmp += int(el)
    return np.sum(top3)


with open('input.txt') as f:
    lines = f.readlines()
    cleanLines = []
    for line in lines:
        cleanLines.append(line.strip())
    cleanLines.append('')

print(f'DAY01_1 RESULT: {execute1(cleanLines)}')
print(f'DAY01_2 RESULT: {execute2(cleanLines)}')