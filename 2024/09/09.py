from collections import defaultdict
import heapq


data = open("input").read().splitlines()[0]

new_arr = []

for idx, char in enumerate(data):
    if idx % 2 == 1:
        hi = "."
    else:
        hi = idx // 2
    for _ in range(int(char)):
        new_arr.append(hi)

amount_dots = new_arr.count(".")
amount_nums = len(new_arr) - amount_dots

copied_arr = new_arr[:amount_nums]

num_side = [x for x in new_arr[amount_nums::] if x != "."]

for idx, item in enumerate(copied_arr):
    if len(num_side) == 0:
        break
    if item == ".":
        copied_arr[idx] = num_side.pop()

checksum = 0
for idx, item in enumerate(copied_arr):
    checksum += idx * item

print(checksum)

checksum = 0

files = {}
freespace = defaultdict(list)
start = 0
for idx, item in enumerate(map(int, data)):
    if idx % 2 == 1:
        heapq.heappush(freespace[item], start)
    else:
        files[idx // 2] = start, item
    start += item

for id in range(max(files), 0, -1):
    i, n = files[id]
    freespaces = sorted([[freespace[free_l][0],free_l] for free_l in freespace if free_l>=n])
    if freespaces:
        start, l = freespaces[0]
        if i > start:
            files[id] = start, n
            remaining_l = l - n
            heapq.heappop(freespace[l])
            if not freespace[l]:
                del freespaces[l]
            if remaining_l:
                heapq.heappush(freespace[remaining_l], start + n)

for num, (start, length) in files.items():
    checksum += num*(start*length+(length*(length-1))//2)

print(checksum)