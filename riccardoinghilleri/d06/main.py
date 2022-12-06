def mark(length):
    global input
    for i in range(length - 1, len(input)):
        found = True
        str = input[i - (length - 1): i + 1]
        for ch in str:
            if str.count(ch) > 1:
                found = False
                break
        if found:
            return i + 1


with open('input.txt') as file:
    input = file.read()
print(mark(4))
print(mark(14))
