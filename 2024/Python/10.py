data = open("input").read().splitlines()

H = len(data)
W = len(data[0])

dydx = [(0, 1), (1, 0), (-1, 0), (0, -1)]


def valid_coord(pos):
    return 0 <= pos[0] < H and 0 <= pos[1] < W


def new_coords(intial_pos):
    y, x = intial_pos
    new_coords = []
    for dy, dx in dydx:
        if valid_coord((y + dy, x + dx)):
            new_coords.append((y + dy, x + dx))
    return new_coords


start = []
for y, line in enumerate(data):
    for x, num in enumerate(line):
        if num == "0":
            start.append((y, x))


def dfs(initial, part2=False, visited=None):
    if visited is None or part2:
        visited = set()
    if initial in visited:
        return 0
    visited.add(initial)
    y, x = initial
    val = int(data[y][x])
    if val == 9:
        return 1
    sum = 0
    for coord in new_coords(initial):
        new_y, new_x = coord
        if data[new_y][new_x] == ".":
            continue
        new_val = int(data[new_y][new_x])
        if new_val == val + 1:
            sum += dfs(coord, part2, visited)
    return sum


scores = 0
ratings = 0

for init in start:
    scores += dfs(init)
    ratings += dfs(init, True)

print(scores, ratings)
