from itertools import product

schems = [schem.splitlines() for schem in open("../inputs/25.txt").read().split("\n\n")]

locks = []
keys = []

for schem in schems:
    if schem[0][0] == "#":
        locks.append(schem)
    else:
        keys.append(schem)

def is_compatible(lock, key):
    for y, row in enumerate(lock):
        for x, item in enumerate(row):
            if item == "#" and key[y][x] == "#":
                return False
    return True

print(sum([is_compatible(lock, key) for lock, key in product(locks, keys)]))
