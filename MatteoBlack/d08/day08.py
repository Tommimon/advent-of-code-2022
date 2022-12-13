import numpy as np


def execute1(input: list) -> int:
    result = 2 * len(input) + 2 * len(input[0]) - 4
    for r in range(1, len(input) - 1):
        for c in range(1, len(input[r]) - 1):
            if input[r][c] > np.max(input[r + 1:, c]) or input[r][c] > np.max(input[:r, c]) or \
                    input[r][c] > np.max(input[r, c + 1:]) or input[r][c] > np.max(input[r, :c]):
                result += 1
    return result


def execute2(input: list) -> int:
    result = []
    for r in range(1, len(input) - 1):
        for c in range(1, len(input[r]) - 1):
            score = 1
            for i in range(r + 1, len(input)):
                if input[r, c] <= input[i, c] or i == len(input[r]) - 1:
                    score *= (i - r)
                    break
            for i in range(c + 1, len(input[r])):
                if input[r, c] <= input[r, i] or i == len(input[r]) - 1:
                    score *= (i - c)
                    break
            for i in range(r - 1, -1, -1):
                if input[r, c] <= input[i, c] or i == 0:
                    score *= (r - i)
                    break
            for i in range(c - 1, -1, -1):
                if input[r, c] <= input[r, i] or i == 0:
                    score *= (c - i)
                    break
            result.append(score)
    return np.max(result)


with open('input.txt') as f:
    lines = f.readlines()
    treeMap = []
    for line in lines:
        treeMap.append([*line.strip()])
    treeMap = np.array(treeMap, dtype=np.int64)

print(f'DAY08_1 RESULT: {execute1(treeMap)}')
print(f'DAY08_2 RESULT: {execute2(treeMap)}')
