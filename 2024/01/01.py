lst_one = []
lst_two = []

for _ in range(1000):
    in_one, in_two = map(int, input().split())
    lst_one.append(in_one)
    lst_two.append(in_two)

lst_one.sort()
lst_two.sort()

counter = 0

for idx, item in enumerate(lst_one):
    counter += abs(item - lst_two[idx])

print(counter)

from collections import Counter

similarity = 0

items_counter = Counter(lst_two)

for idx, item in enumerate(lst_one):
    similarity += item * items_counter[item]

print(similarity)
