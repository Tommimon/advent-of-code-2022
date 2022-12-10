def execute1(input: list) -> int:
    position = set(['0, 0'])
    x_h = y_h = 0
    x_t = y_t = 0
    for el in input:
        direct, step = el.split()
        for s in range(int(step)):
            x_h += 1 if direct == 'R' else 0
            x_h -= 1 if direct == 'L' else 0
            y_h += 1 if direct == 'U' else 0
            y_h -= 1 if direct == 'D' else 0

            if x_h == x_t + 2 and y_h == y_t:
                x_t += 1
            elif x_h == x_t - 2 and y_h == y_t:
                x_t -= 1
            elif y_h == y_t + 2 and x_h == x_t:
                y_t += 1
            elif y_h == y_t - 2 and x_h == x_t:
                y_t -= 1
            elif y_h == y_t + 1 and x_h == x_t + 2:
                y_t += 1
                x_t += 1
            elif y_h == y_t + 2 and x_h == x_t + 1:
                y_t += 1
                x_t += 1
            elif y_h == y_t + 1 and x_h == x_t - 2:
                y_t += 1
                x_t -= 1
            elif y_h == y_t + 2 and x_h == x_t - 1:
                y_t += 1
                x_t -= 1
            elif y_h == y_t - 1 and x_h == x_t - 2:
                y_t -= 1
                x_t -= 1
            elif y_h == y_t - 2 and x_h == x_t - 1:
                y_t -= 1
                x_t -= 1
            elif y_h == y_t - 1 and x_h == x_t + 2:
                y_t -= 1
                x_t += 1
            elif y_h == y_t - 2 and x_h == x_t + 1:
                y_t -= 1
                x_t += 1
            p = str(x_t)
            p += ', '
            p += str(y_t)
            position.add(p)

    return len(position)


def execute2(input: list) -> int:
    snake = [[0, 0] for _ in range(10)]
    position = set(['0, 0'])

    for el in input:
        direct, step = el.split()
        for _ in range(int(step)):
            snake[0][0] += 1 if direct == 'R' else 0
            snake[0][0] -= 1 if direct == 'L' else 0
            snake[0][1] += 1 if direct == 'U' else 0
            snake[0][1] -= 1 if direct == 'D' else 0
            for i in range(1, len(snake)):
                if snake[i - 1][0] == snake[i][0] + 2 and snake[i - 1][1] == snake[i][1]:
                    snake[i][0] += 1
                elif snake[i - 1][0] == snake[i][0] - 2 and snake[i - 1][1] == snake[i][1]:
                    snake[i][0] -= 1
                elif snake[i - 1][1] == snake[i][1] + 2 and snake[i - 1][0] == snake[i][0]:
                    snake[i][1] += 1
                elif snake[i - 1][1] == snake[i][1] - 2 and snake[i - 1][0] == snake[i][0]:
                    snake[i][1] -= 1
                elif snake[i - 1][1] == snake[i][1] + 1 and snake[i - 1][0] == snake[i][0] + 2:
                    snake[i][1] += 1
                    snake[i][0] += 1
                elif snake[i - 1][1] == snake[i][1] + 2 and snake[i - 1][0] == snake[i][0] + 1:
                    snake[i][1] += 1
                    snake[i][0] += 1
                elif snake[i - 1][1] == snake[i][1] + 1 and snake[i - 1][0] == snake[i][0] - 2:
                    snake[i][1] += 1
                    snake[i][0] -= 1
                elif snake[i - 1][1] == snake[i][1] + 2 and snake[i - 1][0] == snake[i][0] - 1:
                    snake[i][1] += 1
                    snake[i][0] -= 1
                elif snake[i - 1][1] == snake[i][1] - 1 and snake[i - 1][0] == snake[i][0] - 2:
                    snake[i][1] -= 1
                    snake[i][0] -= 1
                elif snake[i - 1][1] == snake[i][1] - 2 and snake[i - 1][0] == snake[i][0] - 1:
                    snake[i][1] -= 1
                    snake[i][0] -= 1
                elif snake[i - 1][1] == snake[i][1] - 1 and snake[i - 1][0] == snake[i][0] + 2:
                    snake[i][1] -= 1
                    snake[i][0] += 1
                elif snake[i - 1][1] == snake[i][1] - 2 and snake[i - 1][0] == snake[i][0] + 1:
                    snake[i][1] -= 1
                    snake[i][0] += 1
                elif snake[i - 1][1] == snake[i][1] + 2 and snake[i - 1][0] == snake[i][0] + 2:
                    snake[i][1] += 1
                    snake[i][0] += 1
                elif snake[i - 1][1] == snake[i][1] + 2 and snake[i - 1][0] == snake[i][0] - 2:
                    snake[i][1] += 1
                    snake[i][0] -= 1
                elif snake[i - 1][1] == snake[i][1] - 2 and snake[i - 1][0] == snake[i][0] - 2:
                    snake[i][1] -= 1
                    snake[i][0] -= 1
                elif snake[i - 1][1] == snake[i][1] - 2 and snake[i - 1][0] == snake[i][0] + 2:
                    snake[i][1] -= 1
                    snake[i][0] += 1
            p = str(snake[len(snake) - 1][0])
            p += ', '
            p += str(snake[len(snake) - 1][1])
            position.add(p)

    return len(position)


with open('input.txt') as f:
    lines = f.readlines()
    cleanLines = []
    for line in lines:
        cleanLines.append(line.strip())

print(f'DAY09_1 RESULT: {execute1(cleanLines)}')
print(f'DAY09_2 RESULT: {execute2(cleanLines)}')
