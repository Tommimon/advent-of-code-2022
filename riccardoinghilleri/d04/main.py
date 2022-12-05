results = [0, 0]
with open('input.txt') as file:
    for line in file:
        line = line.replace("-", ",").split(",")
        if (int(line[2]) >= int(line[0]) and int(line[3]) <= int(line[1])) or (int(line[0]) >= int(line[2]) and int(line[1]) <= int(line[3])):
            results[0] += 1
        if (int(line[0]) <= int(line[2]) <= int(line[1])) or (int(line[2]) <= int(line[0]) <= int(line[3])):
            results[1] += 1
print(results)
