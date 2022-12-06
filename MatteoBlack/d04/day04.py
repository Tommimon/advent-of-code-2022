def execute1(input: list) -> int:
    result = 0
    for el in input:
        first, second = el.split(',')
        first_st, first_en = first.split('-')
        second_st, second_en = second.split('-')
        if (int(first_st) >= int(second_st) and int(first_en) <= int(second_en)) or (
                int(first_st) <= int(second_st) and int(first_en) >= int(second_en)):
            result += 1
    return result


def execute2(input: list) -> int:
    result = 0
    for el in input:
        first, second = el.split(',')
        first_st, first_en = first.split('-')
        second_st, second_en = second.split('-')
        if (int(first_en) <= int(second_st) and int(first_st) >= int(second_en)) or (
                int(first_en) >= int(second_st) and int(first_st) <= int(second_en)):
            result += 1
    return result


with open('input.txt') as f:
    lines = f.readlines()
    cleanLines = []
    for line in lines:
        cleanLines.append(line.strip())

print(f'DAY04_1 RESULT: {execute1(cleanLines)}')
print(f'DAY04_2 RESULT: {execute2(cleanLines)}')