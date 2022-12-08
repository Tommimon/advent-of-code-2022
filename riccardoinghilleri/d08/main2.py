import math

with open('input.txt') as file:
    input = file.readlines()
for i in range(len(input)):
    input[i] = input[i].replace("\n", "")
    input[i] = list(map(int, [*input[i]]))
max = 0
for i in range(len(input)):
    for j in range(len(input[i])):
        temp = [0, 0, 0, 0]
        for k in range(i-1, -1, -1):
            if input[k][j] < input[i][j]:
                temp[0] += 1
            else:
                temp[0] += 1
                break
        for k in range(j-1, -1, -1):
            if input[i][k] < input[i][j]:
                temp[1] += 1
            else:
                temp[1] += 1
                break
        for k in range(i + 1, len(input)):
            if input[k][j] < input[i][j]:
                temp[2] += 1
            else:
                temp[2] += 1
                break
        for k in range(j + 1, len(input[i])):
            if input[i][k] < input[i][j]:
                temp[3] += 1
            else:
                temp[3] += 1
                break
        prod = math.prod(temp)
        if prod > max:
            max = prod
        prod = 0
print(max)
