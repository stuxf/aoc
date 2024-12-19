from collections import Counter

dat = open("input").read().splitlines()

left, right = [], []

for line in dat:
    l_id, r_id = map(int, line.split())
    left.append(l_id)
    right.append(r_id)

left.sort(), right.sort()

print(sum(abs(l_id - r_id) for l_id, r_id in zip(left, right)))

id_ctr = Counter(right)

print(sum(l_id * id_ctr[l_id] for l_id in left))
