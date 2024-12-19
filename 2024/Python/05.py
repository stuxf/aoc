from collections import defaultdict
from graphlib import TopologicalSorter

data = open("../inputs/05.txt").read().strip().split("\n\n")
graph = defaultdict(set)

for line in data[0].splitlines():
    first, next = map(int, line.split("|"))
    graph[next].add(first)

updates = [list(map(int, line.split(","))) for line in data[1].splitlines()]


def reorder(sequence):
    subgraph = {n: graph[n] & set(sequence) for n in sequence}
    return list(TopologicalSorter(subgraph).static_order())


middle_sum = 0
middle_sum_corrected = 0

for update in updates:
    new_order = reorder(update)
    if new_order == update:
        middle_sum += update[len(update) // 2]
    else:
        middle_sum_corrected += new_order[len(new_order) // 2]

print(middle_sum)
print(middle_sum_corrected)
