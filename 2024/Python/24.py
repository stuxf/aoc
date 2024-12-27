from collections import defaultdict

raw_wires, raw_gates = open("../inputs/24.txt").read().split("\n\n")

initial_vals = defaultdict(int, {w.split(": ")[0]: int(w.split(": ")[1]) for w in raw_wires.splitlines()})
gates = [g.split() for g in raw_gates.splitlines()]

def simulate(initial_vals, gates):
    vals = initial_vals.copy()
    done = set()
    while len(done) != len(gates):
        ready = {i for i, (a, op, b, _, c) in enumerate(gates) if i not in done and a in vals and b in vals}
        for i in ready:
            a, op, b, _, c = gates[i]
            vals[c] = {'AND': vals[a] & vals[b], 'OR': vals[a] | vals[b], 'XOR': vals[a] ^ vals[b]}[op]
            done.add(i)
    return vals

def bin_to_dec(vals, prefix):
    return int("".join(str(vals[f"{prefix}{i:02}"]) for i in range(45, -1, -1)), 2)

final_vals = simulate(initial_vals, gates)
part1 = bin_to_dec(final_vals, 'z')

z_and_gates = [(i, g) for i, g in enumerate(gates) if g[4].startswith('z') and g[4] != "z45" and g[1] != 'XOR']
non_z_xor_gates = [(i, g) for i, g in enumerate(gates) if g[0][0] not in "xy" and g[2][0] not in "xy" and not g[4].startswith('z') and g[1] == 'XOR']

def find_z_dependency(wire):
    dependents = {i for i, g in enumerate(gates) if g[0] == wire or g[2] == wire}
    for i in dependents:
        if gates[i][4].startswith('z'):
            return "z" + str(int(gates[i][4][1:]) - 1).zfill(2)
    for i in dependents:
        if result := find_z_dependency(gates[i][4]):
            return result
    return None

for i, gate in non_z_xor_gates:
    z_gate_idx = next(zi for zi, zg in z_and_gates if zg[4] == find_z_dependency(gate[4]))
    gates[i][4], gates[z_gate_idx][4] = gates[z_gate_idx][4], gates[i][4]

error_bit_idx = (bin_to_dec(initial_vals, 'x') + bin_to_dec(initial_vals, 'y') ^ bin_to_dec(simulate(initial_vals, gates), 'z')).bit_length() - 1
swapped_wires = sorted({g[4] for _, g in z_and_gates + non_z_xor_gates} | {g[4] for g in gates if g[0].endswith(str(error_bit_idx)) and g[2].endswith(str(error_bit_idx))})

print(part1)
print(",".join(swapped_wires))
