input = open("marcomole00/d08/input").read().split("\n")

f = [[int(y) for y in x] for x in input]

visibles_trees = {(i,j):[] for i in range(1,99) for j in range(1,99)}

visible = 2*len(f) + 2*len(f[0]) -4
print(visible)
scenic_scores = {(i,j):int() for i in range(1,99) for j in range(1,99)}

print(f)

# A tree is visible if all of the other trees between it and an edge of the grid are shorter than it. 
# Only consider trees in the same row or column; that is, only look up, down, left, or right from any given tree.

for i in range (1,len(f)-1):
    for j in range(1,len(f[0])-1):
        tree_up, tree_right, tree_down, tree_left = (False,False,False,False)
        scenic_score = [0,0,0,0]
        
        #up
        for d in range(i-1,-1,-1):
                scenic_score[0]+=1
                if (f[d][j] >= f[i][j]): 
                        tree_up = True
                        break
        if not tree_up : visibles_trees[(i,j)].append("up")
        
        #down
        for d in range(i+1,len(f)):
                scenic_score[1]+=1
                if (f[d][j] >= f[i][j]):
                         tree_down = True
                         break
                

        if not tree_down: visibles_trees[(i,j)].append("down")

        #left 
        for d in range(j-1,-1,-1):
                scenic_score[2]+=1
                if (f[i][d] >= f[i][j]):
                         tree_left = True
                         break
                

        if not tree_left: visibles_trees[(i,j)].append("left")
        
        #right
        for d in range(j+1,len(f[0])):
                scenic_score[3]+=1
                if (f[i][d] >= f[i][j]):
                         tree_right = True
                         break
                
        if  not tree_right : visibles_trees[(i,j)].append("right")

        scenic_scores[i,j] = scenic_score[0]*scenic_score[1]*scenic_score[2]*scenic_score[3]

for keys,values in visibles_trees.items():
        if values != []:
                visible += 1
                print(keys,values)




print(visible)

print(max( scenic_scores.values()))

