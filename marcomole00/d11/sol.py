import re

monkeys = []

input = list(map(lambda s: s.split("\n"), open("marcomole00/d11/input.txt").read().split("\n\n")))

modulo_operator_constant = 1

for monkey in input:
    m = { 
    "number": int(re.findall( "\d", monkey[0])[0]),
    "items" : list(map(int, re.findall("\d+", monkey[1]))),
    "operation" : monkey[2].replace("Operation: new = ", "").strip(),
    "divisible" : int(monkey[3].split()[-1]),
    "true" : int(monkey[4].strip()[-1]),
    "false" : int(monkey[5].strip()[-1]),
    "items_seen" :0
    }
    modulo_operator_constant *= m["divisible"]
    monkeys.append(m)

for round in range(1, 21):
    for m in monkeys:
        while m["items"] != []:
            old_item = m["items"].pop(0)
            item = ( eval(m["operation"].replace("old",str(old_item))) //3 ) % modulo_operator_constant
            #print(old_item,item, m["operation"])
            if item % m["divisible"] == 0: monkeys[m["true"]]["items"].append(item) 
            else: monkeys[m["false"]]["items"].append(item)
            m["items_seen"] += 1
    
   # print("round: ", round)
    p1 = []
    for m in monkeys: 
        #print(f'{m["number"]}: {m["items_seen"]}')
        p1.append(m["items_seen"])

print(sorted(p1))


monkeys.clear()

for monkey in input:
    m = { 
    "number": int(re.findall( "\d", monkey[0])[0]),
    "items" : list(map(int, re.findall("\d+", monkey[1]))),
    "operation" : monkey[2].replace("Operation: new = ", "").strip(),
    "divisible" : int(monkey[3].split()[-1]),
    "true" : int(monkey[4].strip()[-1]),
    "false" : int(monkey[5].strip()[-1]),
    "items_seen" :0
    }
    modulo_operator_constant *= m["divisible"]
    monkeys.append(m)

for round in range(1, 10001):
    for m in monkeys:
        while m["items"] != []:
            old_item = m["items"].pop(0)
            item = ( eval(m["operation"].replace("old",str(old_item))) ) % modulo_operator_constant
            #print(old_item,item, m["operation"])
            if item % m["divisible"] == 0: monkeys[m["true"]]["items"].append(item) 
            else: monkeys[m["false"]]["items"].append(item)
            m["items_seen"] += 1
    
   # print("round: ", round)
    p2 = []
    for m in monkeys: 
        #print(f'{m["number"]}: {m["items_seen"]}')
        p2.append(m["items_seen"])

print(sorted(p2))



