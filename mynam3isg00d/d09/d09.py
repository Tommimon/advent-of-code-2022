import math

def sign(a):
    if (a == 0):
        return 0
    return abs(a)/a

def d09(n): 
    pos = [(0, 0)]
    knots = [(0, 0) for i in range(0, n)]
    for instr in open("input.txt"):
        for i in range(0, int(instr[1:])):
            for k in range(1, len(knots)):
                head = knots[k-1]
                tail = knots[k]
                if (k == 1):
                    knots[k-1] = head = (head[0] + (instr[0] == "R" or instr[0] == "L") * 2 * (0.5 - (instr[0] == "L")), 
                                        head[1] + (instr[0] == "U" or instr[0] == "D") * 2 * (0.5 - (instr[0] == "D")))
                if (math.dist(head, tail) > math.sqrt(2)):
                    knots[k] = (tail[0] + sign(head[0] - tail[0]), tail[1] + sign(head[1] - tail[1]))
                if (k == len(knots)-1):
                    pos.append(knots[k])
    return len(set(pos))

print(f"Part 1: {d09(2)}")
print(f"Part 2: {d09(10)}")