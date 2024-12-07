data = open("input").read().splitlines()

calibrations = []

num_valid = 0
num_valid_tolerances = 0

def all_valid(arr_nums):
    if len(arr_nums) == 1:
        return [arr_nums[0]]
    return [arr_nums[0] * num for num in all_valid(arr_nums[1:])] + [arr_nums[0] + num for num in all_valid(arr_nums[1:])] + [int(str(num) + str(arr_nums[0])) for num in all_valid(arr_nums[1:])]

def all_valid_two(arr_nums):
    if len(arr_nums) == 1:
        return [arr_nums[0]]
    return [arr_nums[0] * num for num in all_valid(arr_nums[1:])] + [arr_nums[0] + num for num in all_valid(arr_nums[1:])] + [int(str(num) + str(arr_nums[0])) for num in all_valid(arr_nums[1:])]

for line in data:
    a = int(line.split(":")[0])
    b = [*map(int, line.split(":")[1].strip().split())]
    calibrations.append((a, b))
    if a in all_valid(b[::-1]):
        num_valid += a
    elif a in all_valid_two(b[::-1]):
        num_valid_tolerances += a

print(num_valid, num_valid_tolerances)