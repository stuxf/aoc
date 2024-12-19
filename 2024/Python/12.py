from collections import deque

data = open("../inputs/12.txt").read().splitlines()

H = len(data)
W = len(data[0])

dydx = [(0, 1), (1, 0), (-1, 0), (0, -1)]


def in_bounds(y, x):
    return 0 <= x < W and 0 <= y < H


def search_alg(y, x):
    rep_item = data[y][x]
    region = set()
    region.add((y, x))
    search = deque([(y, x)])
    while search:
        new_y, new_x = search.pop()
        for dy, dx in dydx:
            if (
                in_bounds(new_y + dy, new_x + dx)
                and data[new_y + dy][new_x + dx] == rep_item
                and (new_y + dy, new_x + dx) not in region
            ):
                region.add((new_y + dy, new_x + dx))
                search.append((new_y + dy, new_x + dx))
    return region


def find_perimeter(region):
    perimeter = 0
    for y, x in region:
        for dy, dx in dydx:
            if (y + dy, x + dx) not in region:
                perimeter += 1
    return perimeter


def find_sides(region):
    corners = 0
    for y, x in region:
        corner_checks = [
            [(0, 1), (1, 0)],
            [(0, 1), (-1, 0)],
            [(0, -1), (-1, 0)],
            [(0, -1), (1, 0)],
        ]

        rep_item = data[y][x]
        for (dy1, dx1), (dy2, dx2) in corner_checks:
            pos1 = (y + dy1, x + dx1)
            pos2 = (y + dy2, x + dx2)
            corner_pos = (y + dy1 + dy2, x + dx1 + dx2)

            is_outer = (
                not in_bounds(*pos1) or data[pos1[0]][pos1[1]] != rep_item
            ) and (not in_bounds(*pos2) or data[pos2[0]][pos2[1]] != rep_item)

            is_inner = (
                in_bounds(*pos1)
                and data[pos1[0]][pos1[1]] == rep_item
                and in_bounds(*pos2)
                and data[pos2[0]][pos2[1]] == rep_item
                and (
                    not in_bounds(*corner_pos)
                    or data[corner_pos[0]][corner_pos[1]] != rep_item
                )
            )

            if is_outer or is_inner:
                corners += 1

    return corners


visited = set()

prices_one = 0
prices_two = 0

for y, line in enumerate(data):
    for x, plant in enumerate(line):
        if (y, x) in visited:
            continue
        region = search_alg(y, x)
        visited.update(region)
        area = len(region)
        perimeter = find_perimeter(region)
        sides = find_sides(region)
        prices_one += area * perimeter
        prices_two += area * sides

print(prices_one)
print(prices_two)
