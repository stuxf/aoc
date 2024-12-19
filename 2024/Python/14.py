from collections import Counter
import math

data = open("../inputs/14.txt").read().splitlines()

W = 101
H = 103

quadrants = [0,0,0,0,0]

def quadrant_id(coords):
    x, y = coords
    if y > H // 2 and x > W // 2:
        return 1
    elif y > H // 2 and x < W // 2:
        return 2
    elif y < H // 2 and x > W // 2:
        return 3
    elif y < H // 2 and x < W // 2:
        return 4
    else:
        return 0

def simulate_robot(p, v, steps=100):
    px, py = p
    vx, vy = v
    return ((px + steps * vx) % W, (py + steps * vy) % H)

robots = []

for line in data:
    p, v = line.split(" ")
    p = tuple(map(int, p[2:].split(",")))
    v = tuple(map(int, v[2:].split(",")))
    robots.append((p, v))
    quadrants[quadrant_id(simulate_robot(p, v))] += 1

print(math.prod(quadrants[1:]))

for i in range(10000):
    grid = Counter()
    for p, v in robots:
        grid[simulate_robot(p, v, steps=i)] += 1
    
    if all(grid[(x, y)] == 1 for x, y in grid):
        print(i)
        break


