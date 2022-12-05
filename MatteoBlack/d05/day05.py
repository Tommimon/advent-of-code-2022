import copy
import re


def execute1(state_1: list, input: list) -> str:
    result = ''
    for el in input:
        qt, fr, to = (re.sub('move\\s|from\\s|to\\s', '', el)).split(' ')

        for _ in range(int(qt)):
            if len(state_1[int(fr) - 1]) > 0:
                state_1[int(to) - 1].insert(0, state_1[int(fr) - 1].pop(0))
    for crate in state_1:
        if len(crate) > 0:
            result += crate.pop(0)
    return result


def execute2(state_2, input: list) -> str:
    result = ''
    for el in input:
        qt, fr, to = (re.sub('move\\s|from\\s|to\\s', '', el)).split(' ')
        multCarry = []
        for _ in range(int(qt)):
            if len(state_2[int(fr) - 1]) > 0:
                multCarry.append(state_2[int(fr) - 1].pop(0))
        for i in range(len(multCarry)):
            state_2[int(to) - 1].insert(i, multCarry[i])
    for crate in state_2:
        if len(crate) > 0:
            result += crate.pop(0)
    return result


with open('input.txt') as f:
    lines = f.readlines()
    moves = []
    tmpState = []
    mov = False
    for line in lines:
        if line.strip() == '':
            mov = True
        elif mov:
            moves.append(line.strip())
        else:
            tmpState.append(line[:-1])

    state = [[] for _ in range(int(tmpState[-1][-1]))]
    for i, s in enumerate(tmpState):
        for j in range(1, len(s), 4):
            focus = ([*s])[j]
            if focus != ' ' and (ord('A') <= ord(focus) <= ord('Z')):
                state[j // 4].append(focus)

print(f'DAY05_1 RESULT: {execute1(copy.deepcopy(state), moves)}')
print(f'DAY05_2 RESULT: {execute2(copy.deepcopy(state), moves)}')
