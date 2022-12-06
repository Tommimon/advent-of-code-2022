import re

f = open("marcomole00/d05/input","r").read().split("\n")

piles = [list() for i in range(0,9)]

for l in f:
    if len(l) == 0: continue
    if l[0] == '[':
        print(l)
        for (index, char) in enumerate(l):
            if (index % 4 == 1) and char != ' ':
                piles[index//4].append(char)
    elif  l[0] == 'm':
      amount, p0,p1 = map(int,re.findall('(\d+)',l))
      for i in range(0,amount):
        if(len(piles[p0-1]) == 0): break
        piles[p1-1].insert(0,piles[p0-1].pop(0))


sol1 = ""
for p in piles:
    sol1 += p[0]

print(sol1)
print(*[*zip(*piles)][0]) 

### part2

piles = ["" for i in range(0,9)]

for l in f:
    if len(l) == 0: continue
    if l[0] == '[':
      #
        for (index, char) in enumerate(l):
            if (index % 4 == 1) and char != ' ':
                piles[index//4] += char
    elif l[0] == 'm':
         amount, p0,p1 = map(int,re.findall('(\d+)',l))
         piles[p1-1] = piles[p0-1][0:amount] + piles[p1-1]
         piles[p0-1] = piles[p0-1][amount:]


sol2 = ""
for p in piles:
    sol2 += p[0]

print(sol2)
