from collections import defaultdict
from itertools import combinations

data = [line.strip() for line in open("../inputs/08.txt")]
H, W = len(data), len(data[0])

antennas = defaultdict(list)
for y, row in enumerate(data):
    for x, char in enumerate(row):
        if char != ".":
            antennas[char].append((y, x))

def count_all_antinodes(antennas):
    basic, extended = set(), set()
    
    for positions in antennas.values():
        for (y1, x1), (y2, x2) in combinations(positions, 2):
            dy, dx = y2 - y1, x2 - x1
            
            if 0 <= y1 - dy < H and 0 <= x1 - dx < W:
                basic.add((y1 - dy, x1 - dx))
                extended.add((y1 - dy, x1 - dx))
            
            if 0 <= y2 + dy < H and 0 <= x2 + dx < W:
                basic.add((y2 + dy, x2 + dx))
                extended.add((y2 + dy, x2 + dx))
            
            mult = 2
            while True:
                new_y, new_x = y1 - mult * dy, x1 - mult * dx
                if not (0 <= new_y < H and 0 <= new_x < W):
                    break
                extended.add((new_y, new_x))
                mult += 1
            
            mult = 2
            while True:
                new_y, new_x = y2 + mult * dy, x2 + mult * dx
                if not (0 <= new_y < H and 0 <= new_x < W):
                    break
                extended.add((new_y, new_x))
                mult += 1
    
    return len(basic), len(extended)

antinodes, antinodes_updated = count_all_antinodes(antennas)
print(antinodes)
print(antinodes_updated)