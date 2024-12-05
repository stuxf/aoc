from collections import defaultdict

data = open("input").read().splitlines()


def isOrdered(update):
    for idx, item in enumerate(update):
        if len(order_dict[item]) != 0:
            for next in order_dict[item]:
                try:
                    if update.index(next) > idx:
                        return False
                except ValueError:
                    pass
    return True


def reordered(update):
    if isOrdered(update):
        return update
    new_update = []
    for idx, item in enumerate(update):
        if len(order_dict[item]) != 0:
            for next in order_dict[item]:
                if next not in new_update and next in update:
                    new_update.append(next)
        if item not in new_update:
            new_update.append(item)
    return reordered(new_update)


ordered_tuples = []

order_dict = defaultdict(list)

updates = []
for line in data:
    if len(line) == 5:
        first, next = map(int, line.split("|"))
        ordered_tuples.append((first, next))
        order_dict[next].append(first)
    elif line != "":
        updates.append([*map(int, line.split(","))])

middle_sum = 0
middle_sum_corrected = 0
for update in updates:
    if isOrdered(update):
        middle_sum += update[len(update) // 2]
    else:
        new_update = reordered(update)
        assert isOrdered(new_update)
        middle_sum_corrected += new_update[len(new_update) // 2]


print(middle_sum)

print(middle_sum_corrected)
