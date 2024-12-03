import re
data = "".join(open("input").read().splitlines())
p = re.compile(r'mul\(\d+,[0-9]+\)')

sum_one = 0
for match in p.findall(data):
    a, b = map(int,match[4:-1].split(","))
    sum_one += a*b

print(sum_one)

p2 = re.compile(r'mul\(\d+,\d+\)|do\(\)|don\'t\(\)')

do = True

sum = 0

for match in p2.findall(data):
    if match == "do()":
        do = True
    elif match == "don't()":
        do = False
    else:
        if do:
            a, b = map(int,match[4:-1].split(","))
            sum += a*b

print(sum)