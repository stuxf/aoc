data = open("../inputs/07.txt").read().splitlines()

num_valid = 0
num_valid_tolerances = 0


def all_valid(arr_nums, res):
    if len(arr_nums) == 1:
        return [arr_nums[0]]
    return [
        s
        for num in all_valid(arr_nums[1:], res)
        for s in (arr_nums[0] + num, arr_nums[0] * num)
        if s <= res
    ]


def all_valid_two(arr_nums, res):
    if len(arr_nums) == 1:
        return [arr_nums[0]]
    return [
        s
        for num in all_valid_two(arr_nums[1:], res)
        for s in (
            arr_nums[0] + num,
            arr_nums[0] * num,
            num * 10 ** len(str(arr_nums[0])) + arr_nums[0],
        )
        if s <= res
    ]


for line in data:
    a = int(line.split(":")[0])
    b = [*map(int, line.split(":")[1].strip().split())][::-1]
    if a in all_valid(b, a):
        num_valid += a
    elif a in all_valid_two(b, a):
        num_valid_tolerances += a

print(num_valid, num_valid_tolerances)
