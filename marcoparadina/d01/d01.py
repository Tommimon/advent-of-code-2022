with open('marcoparadina/d01/input.txt') as f:
    lines = f.readlines()

curr = 0 
ranking = [0,0,0]
res=0

for l in lines:
    if l == '\n':
        for i in range(len(ranking)):
            if curr > ranking[i]:
                ranking[i] = curr
                ranking.sort()
                break
        curr = 0
    else:
        curr+=int(l)

for i in range(len(ranking)):
    if curr > ranking[i]:
        ranking[i] = curr
        ranking.sort()
        break

for i in ranking:
    res+=i
print(ranking)
print(res)

    
