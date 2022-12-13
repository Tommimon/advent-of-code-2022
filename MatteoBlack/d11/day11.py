import copy
import numpy as np


def execute1(input: list) -> int:
    inspectingCounter = np.zeros(len(monkeyList))
    for r in range(20):
        for monkeyId in range(len(input)):
            for obj in input[monkeyId][0]:
                inspectingCounter[monkeyId] += 1
                if input[monkeyId][1] == '*':
                    obj *= int(input[monkeyId][2]) if input[monkeyId][2].isdigit() else obj
                elif input[monkeyId][1] == '+':
                    obj += int(input[monkeyId][2]) if input[monkeyId][2].isdigit() else obj
                obj = obj // 3
                input[monkeyId][0] = np.delete(input[monkeyId][0], 0)

                if obj % input[monkeyId][3] == 0:
                    input[input[monkeyId][4]][0] = np.append(input[input[monkeyId][4]][0], obj)
                else:
                    input[input[monkeyId][5]][0] = np.append(input[input[monkeyId][5]][0], obj)
    inspectingCounter = sorted(inspectingCounter, reverse=True)
    return int(inspectingCounter[0] * inspectingCounter[1])


def execute2(input: list) -> int:
    inspectingCounter = np.zeros(len(monkeyList))

    worryLevel = 1
    for m in input:
        worryLevel *= m[3]
    for r in range(10000):
        for monkeyId in range(len(input)):
            for obj in input[monkeyId][0]:
                inspectingCounter[monkeyId] += 1
                if input[monkeyId][1] == '*':
                    obj *= int(input[monkeyId][2]) if input[monkeyId][2].isdigit() else obj
                elif input[monkeyId][1] == '+':
                    obj += int(input[monkeyId][2]) if input[monkeyId][2].isdigit() else obj
                input[monkeyId][0] = np.delete(input[monkeyId][0], 0)
                obj = obj % worryLevel
                if obj % input[monkeyId][3] == 0:
                    input[input[monkeyId][4]][0] = np.append(input[input[monkeyId][4]][0], obj)
                else:
                    input[input[monkeyId][5]][0] = np.append(input[input[monkeyId][5]][0], obj)
    inspectingCounter = sorted(inspectingCounter, reverse=True)
    return int(inspectingCounter[0] * inspectingCounter[1])
#(1*2)+3 = 5 -> 1+3 * 3+2 = 20
#(1+2)*3 = 9 -> 3 + 6 = 9

with open('input.txt') as f:
    lines = f.readlines()
    monkeyList = []
    for line in lines:
        line = line.strip()
        if line == '':
            continue
        elif 'Monkey' in line:
            monkeyList.append([])
        elif 'Starting' in line:
            tmp = line.split(': ')
            listObj = tmp[1].split(', ')
            listObj = np.array(listObj, dtype=np.longlong)
            monkeyList[len(monkeyList) - 1].append(listObj)
        elif 'Operation' in line:
            monkeyList[len(monkeyList) - 1].append(line.split()[4])
            monkeyList[len(monkeyList) - 1].append(line.split()[5])
        elif 'Test' in line:
            monkeyList[len(monkeyList) - 1].append(int(line.split()[3]))
        elif 'true' in line:
            monkeyList[len(monkeyList) - 1].append(int(line.split()[5]))
        elif 'false' in line:
            monkeyList[len(monkeyList) - 1].append(int(line.split()[5]))

print(f'DAY11_1 RESULT: {execute1(copy.deepcopy(monkeyList))}')
print(f'DAY11_2 RESULT: {execute2(copy.deepcopy(monkeyList))}')
