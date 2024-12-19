data = open("../inputs/15.txt").read().split("\n\n")

grid, moves = data

grid = [list(line) for line in grid.splitlines()]

H = len(grid)
W = len(grid[0])


def in_bounds(y, x):
    return 0 <= y < H and 0 <= x < W


moves = "".join(move.strip() for move in moves)

move_dirs = {"^": (-1, 0), ">": (0, 1), "<": (0, -1), "v": (1, 0)}

for y, line in enumerate(grid):
    for x, item in enumerate(line):
        if item == "@":
            start_pos = (y, x)


def move_robot(grid, pos, move):
    dy, dx = move_dirs[move]
    r_y, r_x = pos

    i = 0
    dir_items = []
    while True:
        dir_items.append(grid[r_y + i * dy][r_x + i * dx])
        if dir_items[-1] == "#" or grid[r_y + i * dy][r_x + i * dx] == ".":
            break
        i += 1

    if dir_items[-1] == "#":
        return grid, pos

    for j in range(len(dir_items)):
        grid[r_y + j * dy][r_x + j * dx] = dir_items[(j - 1) % len(dir_items)]

    return grid, (r_y + dy, r_x + dx)


pos = start_pos
for move in moves:
    grid, pos = move_robot(grid, pos, move)

print(
    sum(
        100 * y + x
        for y, line in enumerate(grid)
        for x, item in enumerate(line)
        if item == "O"
    )
)

wide_map = {"#": ["#", "#"], ".": [".", "."], "O": ["[", "]"], "@": ["@", "."]}

new_grid = []
for line in data[0].splitlines():
    ln = []
    for char in line:
        ln.extend(wide_map[char])
    new_grid.append(ln)

for y, line in enumerate(new_grid):
    for x, item in enumerate(line):
        if item == "@":
            start_pos = (y, x)

pos = start_pos

horiz = [(0, 1), (0, -1)]


def search(grid, pos, move):
    dy, dx = move_dirs[move]
    y, x = pos
    visited = set()

    def dfs(y, x):
        if not (0 <= y < len(grid) and 0 <= x < len(grid[0])):
            return True, set()
        if grid[y][x] == "#":
            return True, set()
        if grid[y][x] == ".":
            return False, {(y, x)}
        if (y, x) in visited:
            return False, set()

        visited.add((y, x))
        to_move = set()

        if (dy, dx) in horiz:
            stopped, positions = dfs(y + dy, x + dx)
            if stopped:
                return True, set()
            to_move.add((y, x))
            to_move.update(positions)
        else:
            if grid[y][x] == "[":
                stopped, right_pos = dfs(y, x + 1)
                if stopped:
                    return True, set()
                to_move.update(right_pos)
            elif grid[y][x] == "]":
                stopped, left_pos = dfs(y, x - 1)
                if stopped:
                    return True, set()
                to_move.update(left_pos)

            stopped, next_pos = dfs(y + dy, x)
            if stopped:
                return True, set()

            to_move.add((y, x))
            to_move.update(next_pos)

        return False, to_move

    next_y, next_x = y + dy, x + dx
    stopped, positions = dfs(next_y, next_x)
    if stopped:
        return False, set()
    return True, positions


def move_two(grid, pos, move):
    dy, dx = move_dirs[move]
    ry, rx = pos
    can_move, to_move = search(grid, pos, move)
    if not can_move:
        return grid, pos
    positions = list(to_move)
    if dx > 0:
        positions.sort(key=lambda p: -p[1])
    elif dx < 0:
        positions.sort(key=lambda p: p[1])
    elif dy > 0:
        positions.sort(key=lambda p: -p[0])
    else:
        positions.sort(key=lambda p: p[0])
    for y, x in positions:
        if (y - dy, x - dx) in to_move:
            grid[y][x] = grid[y - dy][x - dx]
        else:
            grid[y][x] = "."

    grid[ry][rx] = "."
    grid[ry + dy][rx + dx] = "@"

    return grid, (ry + dy, rx + dx)


for move in moves:
    new_grid, pos = move_two(new_grid, pos, move)

print(
    sum(
        100 * y + x
        for y, line in enumerate(new_grid)
        for x, item in enumerate(line)
        if item == "["
    )
)
