def execute1(input: list) -> int:
    result = 0
    for i, el in enumerate(input):
        size = len(el)
        first = el[:size // 2]
        second = el[size // 2:]
        for c in first:
            if c in second:
                result += ((ord(c) - ord('a') + 1) if c.islower() else (ord(c) - ord('A') + 27))
                break
    return result


def execute2(input: list) -> int:
    result = 0
    for i in range(0, len(input), 3):
        if i == len(input) - 2:
            break
        first = input[i]
        second = input[i + 1]
        third = input[i + 2]
        for c in first:
            if c in second and c in third:
                result += ((ord(c) - ord('a') + 1) if c.islower() else (ord(c) - ord('A') + 27))
                break
    return result


with open('input.txt') as f:
    lines = f.readlines()
    cleanLines = []
    for line in lines:
        cleanLines.append(line.strip())

print(f'DAY03_1 RESULT: {execute1(cleanLines)}')
print(f'DAY03_2 RESULT: {execute2(cleanLines)}')
