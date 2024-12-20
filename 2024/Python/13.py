data = open("../inputs/13.txt").read().splitlines()

claw_machines = []
newest_token = []
for num, line in enumerate(data):
    if num % 4 == 3:
        claw_machines.append(newest_token)
        newest_token = []
    else:
        newest_token.append(
            [*(int(x[2:]) for x in line.split(":")[1].strip().split(", "))]
        )
claw_machines.append(newest_token)

tokens_one = 0
tokens_two = 0

def solve_system(x1, y1, x2, y2, px, py):
    det = x1 * y2 - y1 * x2
    if det == 0:
        return None
    a = (px * y2 - py * x2) / det
    b = (x1 * py - y1 * px) / det
    if a.is_integer() and b.is_integer():
        return int(a), int(b)
    return None

for claw_machine in claw_machines:
    x1, y1 = claw_machine[0]
    x2, y2 = claw_machine[1]
    px, py = claw_machine[2]
    
    solution = solve_system(x1, y1, x2, y2, px, py)
    if solution:
        a, b = solution
        tokens_one += a * 3 + b

    offset = int(1e13)
    solution = solve_system(x1, y1, x2, y2, px + offset, py + offset)
    if solution:
        a, b = solution
        tokens_two += a * 3 + b

print(tokens_one)
print(tokens_two)