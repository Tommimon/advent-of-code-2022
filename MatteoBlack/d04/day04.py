import re


def execute1(state: list, input: list) -> str:
    result = ''
    for el in input:
        qt, fr, to = (re.sub('move\\s|from\\s|to\\s', '', el)).split(' ')

        for _ in range(int(qt)):
            if len(state[int(fr) - 1]) > 0:
                tmp = state[int(fr) - 1].pop(0)
                state[int(to) - 1].insert(0, tmp)
    for crate in state:
        if len(crate) > 0:
            result += crate.pop(0)
    return result


def execute2(state_2, input: list) -> str:
    result = ''
    for el in input:
        qt, fr, to = (re.sub('move\\s|from\\s|to\\s', '', el)).split(' ')
        tmp = []
        for _ in range(int(qt)):
            if len(state_2[int(fr) - 1]) > 0:
                tmp.append(state_2[int(fr) - 1].pop(0))
        for i in range(len(tmp)):
            state_2[int(to) - 1].insert(i, tmp[i])
    for crate in state_2:
        if len(crate) > 0:
            result += crate.pop(0)
    return result


with open('input.txt') as f:
    lines = f.readlines()
    sta = []
    moves = []
    mov = False
    for line in lines:
        if line.strip() == '':
            mov = True
        elif mov:
            moves.append(line.strip())
        else:
            sta.append(line.strip())

    tmp_1 = [['O', 'F', 'L', 'S', 'R'], ['T', 'P', 'G', 'Q', 'Z', 'N'], ['B', 'Q', 'M', 'S'],
             ['Q', 'B', 'C', 'H', 'J', 'Z', 'G', 'T'],
             ['S', 'F', 'N', 'B', 'M', 'H', 'P'], ['G', 'V', 'L', 'S', 'N', 'Q', 'C', 'P'],
             ['F', 'C', 'W'],
             ['M', 'P', 'V', 'W', 'Z', 'G', 'H', 'Q'], ['R', 'N', 'C', 'L', 'D', 'Z', 'G']]
    tmp_4 = [['O', 'F', 'L', 'S', 'R'], ['T', 'P', 'G', 'Q', 'Z', 'N'], ['B', 'Q', 'M', 'S'],
             ['Q', 'B', 'C', 'H', 'J', 'Z', 'G', 'T'],
             ['S', 'F', 'N', 'B', 'M', 'H', 'P'], ['G', 'V', 'L', 'S', 'N', 'Q', 'C', 'P'],
             ['F', 'C', 'W'],
             ['M', 'P', 'V', 'W', 'Z', 'G', 'H', 'Q'], ['R', 'N', 'C', 'L', 'D', 'Z', 'G']]
    tmp_2 = [['N', 'Z'], ['D', 'C', 'M'], ['P']]
    tmp_3 = [['N', 'Z'], ['D', 'C', 'M'], ['P']]

print(f'DAY05_1 RESULT: {execute1(tmp_1, moves)}')
print(f'DAY05_2 RESULT: {execute2(tmp_4, moves)}')
