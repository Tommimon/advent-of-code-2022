dirstack = []
sizes = []
part1 = 0
part2 = 0

def finsize():
    final = dirstack.pop()
    sizes.append(final)
    dirstack.append(dirstack.pop() + final)
    if (final < 100_000):
        return final
    else:
        return 0

for cmd in open("input.txt"):
    if ("$ cd " in cmd):
        if (".." in cmd):
            part1 += finsize()
        else:
            dirstack.append(0)
    else:
        try:
            n = int(cmd.split(" ")[0])
            dirstack.append(dirstack.pop() + n)
        except:
            do_nothing_lol = 0

while (len(dirstack) > 1):
    part1 += finsize()
sizes.append(dirstack[0])

tofree = sorted(sizes)[-1] - 40_000_000
for size in sorted(sizes)[::-1]:
    if size > tofree:
        part2 = size
    else:
        break

print(f"Part 1: {part1}")
print(f"Part 2: {part2}")