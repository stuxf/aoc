data = open("input").read().splitlines()
reports = [[*map(int, line.split())] for line in data]


def safe(lvls):
    if len(lvls) < 2:
        return True
    diffs = [b - a for a, b in zip(lvls, lvls[1:])]
    dec = 1 if diffs[0] > 0 else -1
    return all(0 < abs(d) <= 3 and d * dec > 0 for d in diffs)


def safe_damp(lvls):
    if len(lvls) < 2:
        return True
    dec = lvls[0] < lvls[1]

    for idx, num in enumerate(lvls[1:]):
        d = num - lvls[idx]
        if abs(d) > 3 or abs(d) == 0 or (d < 0 and dec) or (d > 0 and not dec):
            return any(safe(lvls[:i] + lvls[i + 1 :]) for i in (idx - 1, idx, idx + 1))
    return True


print(sum(map(safe, reports)))
print(sum(map(safe_damp, reports)))
