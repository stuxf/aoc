from collections import defaultdict

data = [*map(list, open("input").read().splitlines())]

for y, row in enumerate(data):
    for x, item in enumerate(row):
        if item == "^":
            start = (y, x)

assert data[start[0]][start[1]] == "^"

visited = set()

visited.add(start)

direction = (-1, 0)


def turn(tuple):
    match tuple:
        case (1, 0):
            return (0, -1)
        case (0, 1):
            return (1, 0)
        case (-1, 0):
            return (0, 1)
        case (0, -1):
            return (-1, 0)
        case _:
            return tuple


def update_pos(pos, direction):
    return (pos[0] + direction[0], direction[1] + pos[1])


def in_bounds(tuple):
    return 0 <= x < len(data[0]) and 0 <= y < len(data)


y, x = start[0], start[1]

while True:
    y, x = update_pos((y, x), direction)
    if not in_bounds((y, x)):
        break
    if data[y][x] == "#":
        y, x = update_pos((y, x), (direction[0] * -1, direction[1] * -1))
        direction = turn(direction)
    visited.add((y, x))

print(len(visited))


def hasLoop(o_y, o_x):
    new_visited = set()
    direction = (-1, 0)
    y, x = start[0], start[1]
    new_visited.add((y, x, direction))
    while True:
        y, x = update_pos((y, x), direction)
        if (y, x, direction) in new_visited:
            return True
        if not (0 <= x < len(data[0]) and 0 <= y < len(data)):
            break
        if data[y][x] == "#" or (y == o_y and x == o_x):
            y, x = update_pos((y, x), (direction[0] * -1, direction[1] * -1))
            direction = turn(direction)
        new_visited.add((y, x, direction))
    return False


print(
    sum(
        hasLoop(o_y, o_x)
        for o_y in range(len(data))
        for o_x in range(len(data[0]))
        if data[o_y][o_x] == "."
    )
)