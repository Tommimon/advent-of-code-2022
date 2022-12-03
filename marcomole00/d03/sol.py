f = open("marcomole00/d03/input","r").read().split("\n")

#print(f)

total = {}

points = {}

sum_of_total =0

for index, let in enumerate(range(ord("a"),ord("z")+1)):
    points[chr(let)] = index+1

for index, let in enumerate(range(ord("A"),ord("Z")+1)):
    points[chr(let)] = index+27 



for l in f:
    partial = {}
    
    for i in range(0,int(len(l)/2)):
        partial[l[i]] = 1

    for i in range(int(len(l)/2), len(l)):
        if(l[i] in partial.keys()): partial[l[i]]+=1

    for (key,value) in partial.items():
        if value >= 2:
            if key not in total.keys():
                total[key] =0

            total[key] +=1


print (total)


for key in total.keys():
    sum_of_total += points[key]*total[key]


print(sum_of_total)



### part2
total.clear()
partial.clear()
index =0
for ln, l in enumerate(f):
    
    
    for c in l:
        if c not in partial.keys(): partial[c] = set()
        partial[c].add(ln)

    index += 1

    if index == 3:    
        for (key,value) in partial.items():
            if (len(value) >=3):
                if key not in total.keys(): total[key]=0
                total[key] += 1
        
        partial.clear()
        index =0


print (total)

sum_of_total=0
for key in total.keys():
    sum_of_total += points[key]*total[key]


print(sum_of_total)
