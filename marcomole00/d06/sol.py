f = open("marcomole00/d06/input").read()

def solve(n,f):
    i=0
    while True:
        if len(set(f[i:i+n])) ==n:
            print(f[i:i+n])
            print(i+n)
            break
        else:
            i += 1

solve(4,f)
solve(14,f)