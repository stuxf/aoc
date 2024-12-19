import re

data = "".join(open("../inputs/03.txt").read().splitlines())

sum_one = sum(int(a) * int(b) for a, b in re.findall(r"mul\((\d+),(\d+)\)", data))
print(sum_one)

do = True
sum = 0

for match in re.finditer(r"(?:do\(\)|don\'t\(\))|mul\((\d+),(\d+)\)", data):
    if match.group(0) == "do()":
        do = True
    elif match.group(0) == "don't()":
        do = False
    else:
        sum += int(match.group(1)) * int(match.group(2)) if do else 0

print(sum)
