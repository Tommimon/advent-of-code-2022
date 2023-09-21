monkeys = [[79, 98], [54, 65, 75, 74], [79, 60, 97], [74]]
operations = '*+^+'
arguments = [19, 6, -1, 3]
tests = [23, 19, 13, 17]
true_next = [2, 2, 1, 0]
false_next = [3, 0, 3, 1]


divisor = 23 * 19 * 13 * 17
print(divisor)
inspections = [0, 0, 0, 0]

N_ROUNDS = 10000

f = open('output.txt', 'w')

for _ in range(N_ROUNDS):
    for m_index, el in enumerate(monkeys):
        for wl in el:
            inspections[m_index] += 1
            oper = operations[m_index]

            if oper == '*':
                wl *= arguments[m_index]
            elif oper == '+':
                wl += arguments[m_index]
            else:
                wl = wl** 2
                print(wl%divisor, file=f)

            wl %= divisor

            if wl % tests[m_index] == 0:
                monkeys[true_next[m_index]].append(wl)
            else:
                monkeys[false_next[m_index]].append(wl)
        monkeys[m_index] = []

inspections.sort(reverse=True)
print(inspections)
print(inspections[0] * inspections[1])