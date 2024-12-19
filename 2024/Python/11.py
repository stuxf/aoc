from collections import defaultdict

data = [*map(int, open("../inputs/11.txt").read().splitlines()[0].split())]

stones = defaultdict(int)

for stone in data:
    stones[stone] += 1

def blink(stones):
    new_stones = defaultdict(int)
    for stone, count in stones.items():
        stone_l = len(str(stone))
        if stone == 0:
            new_stones[1] += count
        elif stone_l % 2 == 0:
            new_stones[int(str(stone)[:stone_l//2])] += count
            new_stones[int(str(stone)[stone_l//2:])] += count
        else:
            new_stones[stone * 2024] += count
    return new_stones

for blinks in range(75):
    if blinks == 25:
        print(sum(stones.values()))
    stones = blink(stones)

print(sum(stones.values()))