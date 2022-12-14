f = open("marcomole00/d13/input.txt").read().split("\n\n")



f = list(map(lambda s:  eval( s.replace("\n", ",")  ), f))

## the recursive idea was stolen, i'm too dumb to do recursion at 7 am
def compare(l,r):
    match l,r:
        case int(),int(): return l-r
        case list(),int(): return compare(l,[r])
        case int(),list(): return compare([l],r)
        case list(),list():
            for x,y in zip(l,r):
                res = compare(x,y)
                if res != 0: return res

    return len(l) - len(r)



indices =0

for index,p in enumerate(f):
    index += 1
    l,r = p

    if compare(l,r) < 0 : indices += index

print(indices)

## part2

f = filter( lambda s: s != "" , open("marcomole00/d13/input.txt").read().split("\n"))
f = list(map(lambda s:  eval( s  ), f))

less_than_two = 0
higher_than_six = 0
for p in f:
    if compare(p,[[2]])<0: less_than_two +=1
    if compare([[6]],p)<0: 
        higher_than_six +=1
        print(p)

print((less_than_two+1)* (len(f)+2-higher_than_six))