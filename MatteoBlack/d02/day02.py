# ROCK PAPER SCISSOR
def execute1(input: list) -> int:
    result = 0
    for el in input:
        op, own = el.split(' ')
        if own == 'X':
            scoreInLine = 1
        elif own == 'Y':
            scoreInLine = 2
        elif own == 'Z':
            scoreInLine = 3
        if (own == 'X' and op == 'A') or (own == 'Y' and op == 'B') or (own == 'Z' and op == 'C'):
            scoreInLine += 3
        elif (own == 'X' and op == 'C') or (own == 'Y' and op == 'A') or (own == 'Z' and op == 'B'):
            scoreInLine += 6
        result += scoreInLine
    return result


def execute2(input: list) -> int:
    result = 0
    for el in input:
        op, own = el.split(' ')
        if own == 'X':
            scoreInLine = 0
        elif own == 'Y':
            scoreInLine = 3
        elif own == 'Z':
            scoreInLine = 6
        if (own == 'X' and op == 'B') or (own == 'Y' and op == 'A') or (own == 'Z' and op == 'C'):
            scoreInLine += 1
        elif (own == 'X' and op == 'C') or (own == 'Y' and op == 'B') or (own == 'Z' and op == 'A'):
            scoreInLine += 2
        elif (own == 'X' and op == 'A') or (own == 'Y' and op == 'C') or (own == 'Z' and op == 'B'):
            scoreInLine += 3
        result += scoreInLine
    return result


with open('input.txt') as f:
    lines = f.readlines()
    cleanLines = []
    for line in lines:
        cleanLines.append(line.strip())

print(f'DAY02_1 RESULT: {execute1(cleanLines)}')
print(f'DAY02_2 RESULT: {execute2(cleanLines)}')
