f = open("marcomole00/d01/input","r").readlines()

elves = []

temp =0
for el in f:
    elem = el.strip("\n")
    if elem == "":
        elves.append(temp)
        temp =0
    else:
        temp += int(elem)


elves.sort()

print(elves[-1])

print(elves[-1] + elves[-2] +elves[-3])

print("eval solution")
f2 = sorted(eval(open("marcomole00/d01/input", "r").read().replace("\n\n", ",").replace("\n", "+")))

print(f2[-1], sum(f2[-3:]))
