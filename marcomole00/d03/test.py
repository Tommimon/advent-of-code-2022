
f = open("marcomole00/d03/input","r").read().split("\n")


#part2 = sum(priority(set(x[0]).intersection(set(x[1])).intersection(set(x[2])).pop()) for x in zip(*[iter(data)]*3))


for  x in zip(*[iter(f)]*2):
    print(x)