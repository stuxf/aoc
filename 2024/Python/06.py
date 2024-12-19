data = [list(line) for line in open(f"../inputs/06.txt").read().splitlines()]

H, W = len(data), len(data[0])

start = next(
    (y, x) for y, row in enumerate(data) for x, cell in enumerate(row) if cell == "^"
)

dirs = [(1, 0), (0, -1), (-1, 0), (0, 1)]


def turn(d):
    return dirs[(dirs.index(d) + 1) % 4]


def in_bounds(y, x):
    return 0 <= y < H and 0 <= x < W


def walk():
    visited = set()
    dy, dx = (-1, 0)
    y, x = start
    while True:
        y, x = y + dy, x + dx
        if not in_bounds(y, x):
            break
        if data[y][x] == "#":
            y, x = y - dy, x - dx
            dy, dx = turn((dy, dx))
        visited.add((y, x))
    return visited

def has_loop(o_y, o_x, grid_copy):
    visited = set()
    dy, dx = (-1, 0)
    y, x = start
    visited.add((y, x, dy, dx))
    while True:
        y, x = y + dy, x + dx
        if (y, x, dy, dx) in visited:
            return True
        if not in_bounds(y, x):
            return False
        if grid_copy[y][x] == "#" or (y == o_y and x == o_x):
            y, x = y - dy, x - dx
            dy, dx = turn((dy, dx))
        visited.add((y, x, dy, dx))

path = walk()

print(len(path))

print(
    sum(
        has_loop(o_y, o_x, [row[:] for row in data])
        for o_y, o_x in path
        if data[o_y][o_x] == "."
    )
)
