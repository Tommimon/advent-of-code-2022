
  
file1 = open("/Users/Puricelli/Desktop/puzzle1.txt", 'r')
fruits = [0, 0, 0]

moment_act = 0
  
while True:
  
    line = file1.readline()
  
    if not line:
        break
    
    if line == "\n":
        fruits.sort()
        for i in range(len(fruits)):
            if fruits[i] < moment_act:
                fruits[i] = moment_act
                break
        moment_act = 0
    else:
        moment_act = moment_act + int(line)
    
    
    
    
    
    
    
file1.close()

tot = 0

print("MAXIMUS")

for x in fruits:
    tot = tot + x
    print(x)


print("totTOP3 -> ", tot)

print("\n")
print("DONE")