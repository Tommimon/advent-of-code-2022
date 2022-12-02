temp = 0
best_elves = [0, 0, 0]
sum = 0
with open('input.txt') as file:
    for line in file:
        if line == '\n':
            if temp > min(best_elves):
                best_elves[best_elves.index(min(best_elves))] = temp
            temp = 0
        else:
            temp += int(line[:-1])
print(max(best_elves))
for elem in best_elves:
    sum += elem
print(sum)
