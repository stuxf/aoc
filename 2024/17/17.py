import heapq
from collections import defaultdict

registers, program = open("input").read().split("\n\n")

registers = [int(register.split(": ")[1]) for register in registers.splitlines()]

instructions = list(map(int, program.split(": ")[1].split(",")))

registers = {"A": registers[0], "B": registers[1], "C": registers[2]}


def combo(op):
    val = 0
    if op <= 3:
        val = op
    elif op == 4:
        val = registers["A"]
    elif op == 5:
        val = registers["B"]
    elif op == 6:
        val = registers["C"]
    else:
        print(op)

    return val


def vm(registers, instructions):
    out = []
    instruction_pointer = 0
    while True:
        if instruction_pointer >= len(instructions) - 1 or instruction_pointer < 0:
            break
        instruction = instructions[instruction_pointer]
        operand = instructions[instruction_pointer + 1]

        match instruction:
            case 0:
                registers["A"] = registers["A"] // 2 ** combo(operand)
            case 1:
                registers["B"] ^= operand
            case 2:
                registers["B"] = combo(operand) % 8
            case 3:
                if registers["A"] == 0:
                    instruction_pointer += 2
                    continue
                instruction_pointer = operand
                continue
            case 4:
                registers["B"] ^= registers["C"]
            case 5:
                out.append(combo(operand) % 8)
            case 6:
                registers["B"] = registers["A"] // 2 ** combo(operand)
            case 7:
                registers["C"] = registers["A"] // 2 ** combo(operand)
            case _:
                break

        instruction_pointer += 2

    return out


print(",".join(str(item) for item in vm(registers, instructions)))

"""
Register A: 32916674
Register B: 0
Register C: 0

Program: 2,4,1,1,7,5,0,3,1,4,4,0,5,5,3,0
"""

# B = A % 8
# B = B ^ 1
# C = A >> B
# A = A >> 3
# B = B ^ 4
# B = B ^ C
# out(B % 8)
# loop while A is nonzero

group = 16
counter = 0

counter = 0
while True:
    registers["A"] = 0
    registers["A"] = 0b101 << 48 - 3 * 1
    registers["A"] |= 0b110 << (48 - 3 * 2)
    registers["A"] |= 0b000 << (48 - 3 * 3)
    registers["A"] |= 0b000 << (48 - 3 * 4)
    registers["A"] |= 5 << (48 - 3 * 5)
    registers["A"] |= 3 << (48 - 3 * 6)
    registers["A"] |= 0 << (48 - 3 * 7)
    registers["A"] |= 2 << (48 - 3 * 7)
    registers["A"] |= 7 << (48 - 3 * 8)
    registers["A"] |= 5 << (48 - 3 * 9)
    registers["A"] |= 6 << (48 - 3 * 10)
    registers["A"] |= 0 << (48 - 3 * 11)
    registers["A"] |= 2 << (48 - 3 * 12)
    registers["A"] |= 5 << (48 - 3 * 13)
    registers["A"] |= 0 << (48 - 3 * 14)
    registers["A"] |= 5 << (48 - 3 * 15)
    registers["A"] |= 2 << (48 - 3 * 16)

    registers["B"] = 0
    registers["C"] = 0
    print(registers["A"])
    new_out = vm(registers, instructions)
    if new_out[-group] == instructions[-group]:
        break
    counter += 1
