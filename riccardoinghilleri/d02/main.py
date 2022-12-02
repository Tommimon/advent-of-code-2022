def compare_1(a, b):
    global results, values
    if a == b:
        results[0] += 3
    elif (values[b] - values[a]) == 1 or (values[b] - values[a]) == -2:
        results[0] += 6
    results[0] += values[b]


def compare_2(a, b):
    global results, values
    if b == 'A':
        if a == 'A':
            results[1] += values["C"]
        else:
            results[1] += values[chr(ord(a) - 1)]
    elif b == 'B':
        results[1] += 3 + values[a]
    else:
        if a == 'C':
            results[1] += 6 + values["A"]
        else:
            results[1] += 6 + values[chr(ord(a) + 1)]


values = {"A": 1, "B": 2, "C": 3}
results = [0, 0]
with open('input.txt') as file:
    for line in file:
        line = line.replace("X", "A").replace("Y", "B").replace("Z", "C").split()
        compare_1(line[0], line[1])
        compare_2(line[0], line[1])
print(results[0])
print(results[1])
