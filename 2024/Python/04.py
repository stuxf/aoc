data = open("../inputs/04.txt").read().splitlines()

dxy = [(x, y) for x in range(-1, 2) for y in range(-1, 2) if x or y]
diag = [(-1, -1), (-1, 1), (1, -1), (1, 1)]

TARGET = "XMAS"

search_cnt = 0
revised_search_cnt = 0

for x, row in enumerate(data):
    for y, col in enumerate(row):
        if 0 < x < len(data) - 1 and 0 < y < len(row) - 1:
            corners = [data[x + dx][y + dy] for dx, dy in diag]
            if col == "A" and corners.count("M") == 2 and corners.count("S") == 2 and corners[0] != corners[3]:
                revised_search_cnt += 1
        if col != TARGET[0]:
            continue

        for dx, dy in dxy:
            s = "X"
            for d in range(1, len(TARGET)):
                if 0 <= x + dx * d < len(data) and 0 <= y + dy * d < len(row):
                    s += data[x + dx * d][y + dy * d]
            if s == TARGET:
                search_cnt += 1

print(search_cnt)
print(revised_search_cnt)
