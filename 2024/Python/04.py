data = open("../inputs/04.txt").read().splitlines()

dydx = [(y, x) for y in range(-1, 2) for x in range(-1, 2) if y or x]
diag = [(-1, -1), (-1, 1), (1, -1), (1, 1)]

H = len(data)
W = len(data[0])

search_cnt = 0
revised_search_cnt = 0

for y, row in enumerate(data):
    for x, col in enumerate(row):
        if 0 < y < H - 1 and 0 < x < W - 1:
            corners = [data[y + dx][x + dy] for dx, dy in diag]
            if (
                col == "A"
                and corners.count("M") == 2
                and corners.count("S") == 2
                and corners[0] != corners[3]
            ):
                revised_search_cnt += 1

        if col != "X":
            continue

        for dy, dx in dydx:
            chars = ["X"]
            for d in range(1, 4):
                if 0 <= y + dy * d < H and 0 <= x + dx * d < W:
                    chars.append(data[y + dy * d][x + dx * d])
            if "".join(chars) == "XMAS":
                search_cnt += 1

print(search_cnt)
print(revised_search_cnt)
