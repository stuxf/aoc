data = [
    [int(c) if c != "." else -1 for c in line.strip()]
    for line in open("../inputs/10.txt")
]

H = len(data)
W = len(data[0])

dydx = [(0, 1), (1, 0), (-1, 0), (0, -1)]


def valid_coord(y, x):
    return 0 <= y < H and 0 <= x < W


starts = [(y, x) for y in range(H) for x in range(W) if data[y][x] == 0]


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
    for dy, dx in dydx:
        new_y, new_x = y + dy, x + dx
        if not valid_coord(new_y, new_x) or data[new_y][new_x] == ".":
            continue
        new_val = data[new_y][new_x]
        if new_val == val + 1:
            sum += dfs((new_y, new_x), part2, visited)
    return sum


scores = 0
ratings = 0

for init in starts:
    scores += dfs(init)
    ratings += dfs(init, True)

print(scores)
print(ratings)
