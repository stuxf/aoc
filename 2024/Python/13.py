import z3

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

for claw_machine in claw_machines:
    x1, y1 = claw_machine[0]
    x2, y2 = claw_machine[1]
    px, py = claw_machine[2]
    sol_one = z3.Solver()
    sol_offset = z3.Solver()
    a, b = z3.Ints("a b")
    sol_one.add(a * x1 + b * x2 == px)
    sol_one.add(a * y1 + b * y2 == py)
    sol_offset.add(a * x1 + b * x2 == px + 1e13)
    sol_offset.add(a * y1 + b * y2 == py + 1e13)
    if sol_one.check() == z3.sat:
        m = sol_one.model()
        tokens_one += m[a].as_long() * 3 + m[b].as_long()
    if sol_offset.check() == z3.sat:
        m = sol_offset.model()
        tokens_two += m[a].as_long() * 3 + m[b].as_long()

print(tokens_one)
print(tokens_two)
