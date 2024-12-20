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
            
            mult = 0
            while 0 <= y1 - mult * dy < H and 0 <= x1 - mult * dx < W:
                new_pos = (y1 - mult * dy, x1 - mult * dx)
                extended.add(new_pos)
                if mult == 1:
                    basic.add(new_pos)
                mult += 1
            
            mult = 0
            while 0 <= y2 + mult * dy < H and 0 <= x2 + mult * dx < W:
                new_pos = (y2 + mult * dy, x2 + mult * dx)
                extended.add(new_pos)
                if mult == 1:
                    basic.add(new_pos)
                mult += 1
    
    return len(basic), len(extended)

antinodes, antinodes_updated = count_all_antinodes(antennas)
print(antinodes)
print(antinodes_updated)