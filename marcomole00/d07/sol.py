from itertools import accumulate

f = open("marcomole00/d07/input").read().split("\n")

directories = {'//':0}

current_directory = []

for l in f:
    match l.split():
        case 'dir', dirname :
            directories[''.join(current_directory)+dirname+"/"] = 0
        case "$", 'ls':continue
    
        case '$', 'cd','..': 
            current_directory.pop()
        case '$', 'cd' , x : 
            current_directory.append( x + "/")
        case size , file:
            for i in accumulate(current_directory):
                directories[i] += int(size)
            


p1=0
for val in directories.values():
    if val <= 100000: p1+=val


print(f"part1 is {p1}")


## part2

## Find the smallest directory that,
#  if deleted, would free up enough space on the filesystem to run the update

total = 70000000
update_size= 30000000

dir_size = total
for val in directories.values():
    if  total -int(directories["//"]) + val >= update_size: dir_size= min(dir_size,val)


print(f"part2 is {dir_size}")