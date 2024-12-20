interface Registers {
  A: bigint;
  B: bigint;
  C: bigint;
}

const data = await Deno.readTextFile("../inputs/17.txt");
const [registersRaw, program] = data.split("\n\n");

const registerValues = registersRaw.split("\n").map((r) =>
  BigInt(r.split(": ")[1])
);
const instructions = program.split(": ")[1].split(",").map(Number);

const registers: Registers = {
  A: registerValues[0],
  B: registerValues[1],
  C: registerValues[2],
};

const combo = (op: number): bigint => {
  if (op <= 3) return BigInt(op);
  if (op === 4) return registers.A;
  if (op === 5) return registers.B;
  if (op === 6) return registers.C;
  return 0n;
};

const vm = (regs: Registers, instructions: number[]): number[] => {
  const out: number[] = [];
  let ip = 0;

  while (ip < instructions.length - 1 && ip >= 0) {
    const instruction = instructions[ip];
    const operand = instructions[ip + 1];

    switch (instruction) {
      case 0:
        regs.A = regs.A >> combo(operand);
        break;
      case 1:
        regs.B ^= BigInt(operand);
        break;
      case 2:
        regs.B = combo(operand) % 8n;
        break;
      case 3:
        if (regs.A === 0n) {
          ip += 2;
          continue;
        }
        ip = operand;
        continue;
      case 4:
        regs.B ^= regs.C;
        break;
      case 5:
        out.push(Number(combo(operand) % 8n));
        break;
      case 6:
        regs.B = regs.A >> combo(operand);
        break;
      case 7:
        regs.C = regs.A >> combo(operand);
        break;
      default:
        return out;
    }
    ip += 2;
  }

  return out;
};

console.log(vm(registers, instructions).join(","));

const group = 16;
let counter = 0;

while (true) {
  registers.A = 0n;
  registers.A |= BigInt(0b101) << BigInt(48 - 3 * 1);
  registers.A |= BigInt(0b110) << BigInt(48 - 3 * 2);
  registers.A |= BigInt(0b000) << BigInt(48 - 3 * 3);
  registers.A |= BigInt(0b000) << BigInt(48 - 3 * 4);
  registers.A |= 5n << BigInt(48 - 3 * 5);
  registers.A |= 3n << BigInt(48 - 3 * 6);
  registers.A |= 0n << BigInt(48 - 3 * 7);
  registers.A |= 2n << BigInt(48 - 3 * 7);
  registers.A |= 7n << BigInt(48 - 3 * 8);
  registers.A |= 5n << BigInt(48 - 3 * 9);
  registers.A |= 6n << BigInt(48 - 3 * 10);
  registers.A |= 0n << BigInt(48 - 3 * 11);
  registers.A |= 2n << BigInt(48 - 3 * 12);
  registers.A |= 5n << BigInt(48 - 3 * 13);
  registers.A |= 0n << BigInt(48 - 3 * 14);
  registers.A |= 5n << BigInt(48 - 3 * 15);
  registers.A |= 2n << BigInt(48 - 3 * 16);

  registers.B = 0n;
  registers.C = 0n;

  console.log(registers.A.toString());
  const newOut = vm(registers, instructions);

  if (
    newOut[newOut.length - group] ===
      instructions[instructions.length - group]
  ) {
    break;
  }
  counter++;
}
