import heapq
from collections import defaultdict

data = open("../inputs/16.txt").read().splitlines()

dydx = [(0, 1), (1, 0), (0, -1), (-1, 0)]
H = len(data)
W = len(data[0])

R_COST = 1000
M_COST = 1


def rotate(dir, clockwise):
    dir_idx = dydx.index(dir)
    if clockwise:
        return dydx[(dir_idx + 1) % len(dydx)]
    return dydx[(dir_idx - 1) % len(dydx)]


for y, line in enumerate(data):
    for x, item in enumerate(line):
        if item == "S":
            start_pos = (y, x)
        if item == "E":
            end_pos = (y, x)


def dijkstra(grid, start_pos, start_dir=(0, 1)):
    distances = defaultdict(lambda: float("inf"))

    distances[(start_pos, start_dir)] = 0
    pq = [(0, start_pos, start_dir)]
    while pq:
        cur_distance, cur_pos, cur_dir = heapq.heappop(pq)
        r_y, r_x = cur_pos
        dy, dx = cur_dir

        if cur_distance > distances[(cur_pos, cur_dir)]:
            continue

        if grid[r_y + dy][r_x + dx] != "#":
            distance = cur_distance + M_COST

            if distance < distances[((r_y + dy, r_x + dx), cur_dir)]:
                distances[((r_y + dy, r_x + dx), cur_dir)] = distance
                heapq.heappush(pq, (distance, (r_y + dy, r_x + dx), cur_dir))
        for clockwise in (True, False):
            distance = cur_distance + R_COST
            new_dir = rotate(cur_dir, clockwise)
            if distance < distances[(cur_pos, new_dir)]:
                distances[(cur_pos, new_dir)] = distance
                heapq.heappush(pq, (distance, cur_pos, new_dir))

    return distances


distances = dijkstra(data, start_pos)
print(min(distances[(end_pos, dir)] for dir in dydx))


def paths(distances, end_pos):
    path_positions = set()

    end_distance = min(distances[(end_pos, dir)] for dir in dydx)

    stack = []
    for dir in dydx:
        if distances[(end_pos, dir)] == end_distance:
            stack.append((end_pos, dir, end_distance))

    while stack:
        pos, cur_dir, dist = stack.pop()
        path_positions.add(pos)
        y, x = pos
        dy, dx = cur_dir

        p_y = y - dy
        p_x = x - dx
        if distances[((p_y, p_x), cur_dir)] + M_COST == dist:
            stack.append(((p_y, p_x), cur_dir, distances[((p_y, p_x), cur_dir)]))

        for clockwise in (True, False):
            prev_dir = rotate(cur_dir, clockwise)
            if distances[(pos, prev_dir)] + R_COST == dist:
                stack.append((pos, prev_dir, distances[(pos, prev_dir)]))

    return path_positions


print(len(paths(distances, end_pos)))
