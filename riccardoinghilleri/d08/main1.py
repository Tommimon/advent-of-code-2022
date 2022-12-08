with open('input.txt') as file:
    input = file.readlines()
for i in range(len(input)):
    input[i] = input[i].replace("\n", "")
    input[i] = list(map(int, [*input[i]]))
visible_trees = 2 * len(input) + (len(input[0]) - 2) * 2
for i in range(1, len(input)-1):
    for j in range(1, len(input[i])-1):
        visible = [True, True, True, True]
        for k in range(i):
            if input[k][j] >= input[i][j]:
                visible[0] = False
                break
        for k in range(j):
            if visible[0] is True:
                break
            if input[i][k] >= input[i][j]:
                visible[1] = False
                break
        for k in range(i + 1, len(input)):
            if visible[1] is True:
                break
            if input[k][j] >= input[i][j]:
                visible[2] = False
                break
        for k in range(j + 1, len(input[i])):
            if visible[2] is True:
                break
            if input[i][k] >= input[i][j]:
                visible[3] = False
                break
        if True in visible:
            visible_trees += 1
print(visible_trees)
