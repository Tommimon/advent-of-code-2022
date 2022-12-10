input = iter(open("marcomole00/d10/input").read().split("\n"))

image = [['.' for _ in range(0,40)] for _ in range(0,6)]
x =1
exec = []
cycle =1

p1 =0

while True:
    print(x)
    if cycle in (20,60,100,140,180,220): p1 += cycle*x
    if cycle == 220: break
    if (cycle % 40) -1 in (x-1,x,x+1): image[cycle // 40][(cycle % 40)-1] =  "#"
    if exec ==[]:   
        match next(input).split():
            case "addx",amount: exec.append(int(amount))
            case "noop": pass
    else:
        x += exec.pop()
    
    cycle+=1


print(p1)

for l in image:
    print("".join(l))
