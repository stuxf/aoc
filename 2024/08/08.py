from collections import defaultdict
from itertools import combinations

data = open("input").read().splitlines()

antennas = defaultdict(list)
for y, line in enumerate(data):
    for x, item in enumerate(line):
        if item != ".":
            antennas[item].append((y, x))

valid_antinodes = 0


def find_antinodes(list_ant):
    antinodes = set()
    for item in set(combinations(list_ant, 2)):
        a, b = item[0]
        c, d = item[1]
        dy, dx = c - a, d - b
        antinodes.add((a - dy, b - dx))
        antinodes.add((c + dy, d + dx))

    return antinodes


def find_antinodes_two(list_ant):
    antinodes = set()
    for item in set(combinations(list_ant, 2)):
        a, b = item[0]
        c, d = item[1]
        dy, dx = c - a, d - b
        cntr = 0
        while True:
            if not valid_antinode((a - cntr * dy, b - cntr * dx)):
                break
            antinodes.add((a - cntr * dy, b - cntr * dx))
            cntr += 1
        cntr = 0
        while True:
            if not valid_antinode((a + cntr * dy, b + cntr * dx)):
                break
            antinodes.add((c + cntr * dy, d + cntr * dx))
            cntr += 1

    return antinodes


def valid_antinode(antinode):
    return 0 <= antinode[0] < len(data) and 0 <= antinode[1] < len(data[0])


antinodes = set()
antinodes_two = set()

valid_antinodes_two = 0


for antenna in antennas:
    antinodes = antinodes.union(find_antinodes(antennas[antenna]))
    antinodes_two = antinodes_two.union(find_antinodes_two(antennas[antenna]))
for antinode in antinodes:
    valid_antinodes += valid_antinode(antinode)
for antinode in antinodes_two:
    valid_antinodes_two += valid_antinode(antinode)

print(valid_antinodes, valid_antinodes_two)
