
visited_by_tail = set()



def isNotAdjacent(head:complex,tail:complex) -> bool:
    if abs(head-tail) >= 2: 
        return True
    else: return False


input = open("marcomole00/d09/input").read().split("\n")
head = 0+0j
tail = 0+0j

visited_by_tail.add(tail)



for l in input:        
        match l.split(" "):
            case "R" , amount:
                for i in range(0,int(amount)):
                    if isNotAdjacent(head+1,tail):
                        tail = head
                        visited_by_tail.add(tail)

                    
                    head += 1
            case "L" , amount:
                for i in range(0,int(amount)):
                    if isNotAdjacent(head-1,tail):
                        tail = head
                        visited_by_tail.add(tail)


                    head -= 1
            case "U" , amount:
                for i in range(0,int(amount)):
                    if isNotAdjacent(head+1j,tail):
                        tail = head
                        visited_by_tail.add(tail)

                    head += 1j
            case "D" , amount:
                for i in range(0,int(amount)):
                    if isNotAdjacent(head-1j,tail):
                        tail = head
                        visited_by_tail.add(tail)

                    head -= 1j

        print(f"after {l} -> {head}, {tail}")

            

print(len(visited_by_tail))
print(visited_by_tail)

def sign(val):
    return complex((val.real > 0 ) - (val.real<0) , (val.imag > 0 ) - (val.imag<0))


## part2 now with ten knots!

knots = [ 0+0j for _ in range(0,10)]

seen = [set([0]) for _ in range(0,10)]


for l in input:
    
    dir,amount = l.split()
        
    for _ in range(0,int(amount)):
        match dir:
            case "R":
                knots[0] += 1
            case "L":
                knots[0] -= 1
            case "U":
                knots[0] += 1j
            case "D":
                knots[0] -= 1j
        
        for k in range(1,10):
            distance = knots[k-1] - knots[k]
            if abs(distance) >=2:
                knots[k] += sign(distance)
                seen[k].add(knots[k])
        


    
print(len(seen[9]))

#