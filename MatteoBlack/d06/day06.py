def execute(input: list, size=4) -> int:
    message = [*input[0]]
    for i in range(size - 1, len(message)):
        setChar = set([message[i - j] for j in range(size)])
        if len(setChar) == size:
            return i + 1
    return -1


with open('input.txt') as f:
    lines = f.readlines()
    cleanLines = []
    for line in lines:
        cleanLines.append(line.strip())

print(f'DAY06_1 RESULT: {execute(cleanLines)}')
print(f'DAY06_2 RESULT: {execute(cleanLines, 14)}')
