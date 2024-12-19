from functools import cache

data = open("../inputs/19.txt").read().split("\n\n")

patterns = data[0].split(", ")

towels = data[1].splitlines()


@cache
def possible_designs(towel):
    if not towel:
        return 1

    options = 0
    for pattern in patterns:
        if towel.startswith(pattern):
            options += possible_designs(towel[len(pattern) :])

    return options


print(sum(bool(possible_designs(towel)) for towel in towels))
print(sum(possible_designs(towel) for towel in towels))
