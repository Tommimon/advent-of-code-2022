temp = 0
best_elves = [0, 0, 0]
with open('input.txt') as file:
    for line in file:
        if line == '\n':
            if temp > min(best_elves):
                best_elves[best_elves.index(min(best_elves))] = temp
            temp = 0
        else:
            temp += int(line[:-1])
if temp > min(best_elves):
    best_elves[best_elves.index(min(best_elves))] = temp
print(max(best_elves))
print(sum(best_elves))
