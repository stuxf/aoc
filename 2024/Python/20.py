data = open("../inputs/20.txt").read().splitlines()

grid = set()
start_pos = None

for y, line in enumerate(data):
    for x, item in enumerate(line):
        if item == "S":
            start_pos = (y, x)
        elif item == "#":
            grid.add((y, x))

dydx = [(0, 1), (0, -1), (1, 0), (-1, 0)]


q = [(start_pos, 0)]
visited = {start_pos}
costs = {start_pos: 0}

for (y, x), cost in q:
    for dy, dx in dydx:
        new_pos = (y + dy, x + dx)
        if new_pos not in grid and new_pos not in visited:
            visited.add(new_pos)
            costs[new_pos] = cost + 1
            q.append((new_pos, cost + 1))

cheat = 0
cheat_more = 0
visited_list = list(visited)
costs_list = [costs[pos] for pos in visited_list]

for i in range(len(visited_list)):
    y1, x1 = visited_list[i]
    for j in range(i + 1, len(visited_list)):
        y2, x2 = visited_list[j]
        mh = abs(y1 - y2) + abs(x1 - x2)
        if mh <= 20:
            cost1, cost2 = costs_list[i], costs_list[j]
            if cost2 - cost1 - mh >= 100:
                cheat_more += 1
                if mh == 2:
                    cheat += 1
print(cheat)
print(cheat_more)
