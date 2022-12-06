f = open("marcomole00/d06/input").read()

print(f)


i =0 

while True:
    if len(set(f[i:i+4])) ==4:
        print(f[i:i+4])
        print(i+4)
        break
    else:
        i += 1


while True:
    if len(set(f[i:i+14])) ==14:
        print(f[i:i+14])
        print(i+14)
        break
    else:
        i += 1