results = [0, 0]
group = []
with open('input.txt') as file:
    for line in file:
        line = line.replace("\n", "")
        group.append(line)
        for c in line[:int(len(line) / 2)]:
            if c in line[int(len(line) / 2):]:
                if 'A' <= c <= 'Z':
                    results[0] += ord(c) - 38
                else:
                    results[0] += ord(c) - 96
                break
        if len(group) == 3:
            for c in group[0]:
                if (c in group[1]) and (c in group[2]):
                    if 'A' <= c <= 'Z':
                        results[1] += ord(c) - 38
                    else:
                        results[1] += ord(c) - 96
                    break
            group.clear()
print(results[0])
print(results[1])
