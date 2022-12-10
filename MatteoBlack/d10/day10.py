def execute1(input: list) -> int:
    result = 0
    cycle = 1
    x = 1
    increments = []
    check = 20
    for el in input:
        if 'addx' in el:
            cmd, inc = el.split()
            increments.append(0)
            increments.append(int(inc))
        else:
            increments.append(0)

    for action in increments:
        if cycle == check:
            result += (cycle * x)
            check += 40
        x += action
        cycle += 1
    return result


def execute2(input: list) -> list:
    increments = []
    cycle = 1
    x = 2
    screen = []
    lineCRT = ''
    for el in input:
        if 'addx' in el:
            cmd, inc = el.split()
            increments.append(0)
            increments.append(int(inc))
        else:
            increments.append(0)

    for action in increments:
        pixel = cycle % 40
        if (x - 1 <= pixel <= x + 1 and cycle % 40 != 0) or (x - 1 <= 40 <= x + 1 and cycle % 40 == 0):
            lineCRT += '#'
        else:
            lineCRT += '.'
        if cycle % 40 == 0:
            screen.append(lineCRT)
            lineCRT = ''
        x += action
        cycle += 1
    return screen


with open('input.txt') as f:
    lines = f.readlines()
    cleanLines = []
    for line in lines:
        cleanLines.append(line.strip())

print(f'DAY10_1 RESULT: {execute1(cleanLines)}')
print(f'DAY10_2 RESULT:')
for ln in execute2(cleanLines):
    print(ln)
