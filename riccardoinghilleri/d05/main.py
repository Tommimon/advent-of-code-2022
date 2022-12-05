import copy
part_1 = []
setup = True
with open('input.txt') as file:
    for line in file:
        if len(line) == 1 or line[1] == "1":
            setup = False
            for elem in part_1:
                while ' ' in elem:
                    elem.remove(' ')
            part_2 = copy.deepcopy(part_1)
        elif setup:
            j = 0
            for i in range(1, len(line), 4):
                if len(part_1) <= j:
                    part_1.append(list())
                part_1[j].insert(0, line[i])
                j += 1
        else:
            line = line.replace("\n", "").replace("move", "").replace("from", "").replace("to", "")
            line = line.split()
            for i in range(int(line[0])):
                part_1[int(line[2])-1].append(part_1[int(line[1])-1].pop())
            temp = part_2[int(line[1]) - 1][-int(line[0]):]
            part_2[int(line[1]) - 1] = part_2[int(line[1]) - 1][:-int(line[0])]
            for i in range(int(line[0])):
                part_2[int(line[2]) - 1].append(temp.pop(0))
for column in part_1:
    print(column[-1], end="")
print()
for column in part_2:
    print(column[-1], end="")
