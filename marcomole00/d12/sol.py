file = list(map(list, open("marcomole00/d12/input").read().split("\n")))


input = {(i,j):file[j][i] for i in range(0,len(file[0])) for j in range(0,len(file))}

BFS_info = {(i,j): False for i in range(0,len(file[0])) for j in range(0,len(file))}


start_point = (0,20)
end_point = (36,20)


input[start_point] = 'a'
input[end_point] = 'z'

Q = []

Q.append(start_point)
BFS_info[start_point] = (True,start_point)


while len(Q) > 0:
    v = Q.pop(0)
    
    if v == end_point: break

    for dir in [(+1,0),(-1,0),(0,+1),(0,-1)]:
    
        w = (v[0] + dir[0], v[1] + dir[1] )
        if w not in input.keys(): continue
        
        if ord(input[v]) +1 < ord(input[w]): continue
        
        if BFS_info[w] == False: 
            BFS_info[w] = (True, v)
            Q.append(w)


#print(BFS_info)

s = end_point
step = 0
while s != start_point:
    #print(s, step)
    s= BFS_info[s][1]
    step += 1

print(step)



## part 2

BFS_info.clear()
BFS_info = {(i,j): False for i in range(0,len(file[0])) for j in range(0,len(file))}
start_point = end_point
end_point = (-1,-1)
Q = []

Q.append(start_point)
BFS_info[start_point] = (True,start_point)

while len(Q) > 0:
    v = Q.pop(0)
    
    if input[v] == 'a': 
        end_point = v
        break

    for dir in [(+1,0),(-1,0),(0,+1),(0,-1)]:
        w = (v[0] + dir[0], v[1] + dir[1] )
        if w not in input.keys(): continue
        
        if ord(input[w]) +1 < ord(input[v]): continue
        
        if BFS_info[w] == False: 
            BFS_info[w] = (True, v)
            Q.append(w)

s = end_point
step = 0
while s != start_point:
    #print(s, step)
    s= BFS_info[s][1]
    step += 1

print(step)

