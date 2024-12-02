from collections import Counter

dat = open("input").read().splitlines()

reports = []
for line in dat:
    reports.append([*map(int, line.split())])


def is_safe(report):
    increasing = True
    if report[0] > report[1]:
        increasing = False

    damp = 0

    for idx, num in enumerate(report[1:]):
        val = num - report[idx]
        if abs(val) > 3:
            return False
        if abs(val) == 0:
            return False
        if val < 0 and increasing:
            return False
        elif val > 0 and not increasing:
            return False
    return True


def is_safe_two(report):
    increasing = True
    if report[0] > report[1]:
        increasing = False

    damp = 0

    for idx, num in enumerate(report[1:]):
        val = num - report[idx]
        if abs(val) > 3:
            return (
                is_safe(report[:idx] + report[idx + 1 :])
                or is_safe(report[: idx - 1] + report[idx:])
                or is_safe(report[: idx + 1] + report[idx + 2 :])
            )
        if abs(val) == 0:
            return (
                is_safe(report[:idx] + report[idx + 1 :])
                or is_safe(report[: idx - 1] + report[idx:])
                or is_safe(report[: idx + 1] + report[idx + 2 :])
            )
        if val < 0 and increasing:
            return (
                is_safe(report[:idx] + report[idx + 1 :])
                or is_safe(report[: idx - 1] + report[idx:])
                or is_safe(report[: idx + 1] + report[idx + 2 :])
            )
        elif val > 0 and not increasing:
            return (
                is_safe(report[:idx] + report[idx + 1 :])
                or is_safe(report[: idx - 1] + report[idx:])
                or is_safe(report[: idx + 1] + report[idx + 2 :])
            )
    return True


safe = 0
safe_two = 0

for report in reports:
    if is_safe(report):
        safe += 1
    if is_safe_two(report):
        safe_two += 1
