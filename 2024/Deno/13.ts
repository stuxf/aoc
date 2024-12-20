const data = (await Deno.readTextFile("../inputs/13.txt")).split("\n");

const clawMachines: number[][][] = [];
let newestToken: number[][] = [];
for (let i = 0; i < data.length; i++) {
  if (i % 4 === 3) {
    clawMachines.push(newestToken);
    newestToken = [];
  } else {
    newestToken.push(
      data[i].split(":")[1].trim().split(", ").map((x) => parseInt(x.slice(2))),
    );
  }
}
clawMachines.push(newestToken);

let tokensOne = 0;
let tokensTwo = 0;

function solveSystem(
  x1: number,
  y1: number,
  x2: number,
  y2: number,
  px: number,
  py: number,
): [number, number] | null {
  const det = x1 * y2 - y1 * x2;
  if (det === 0) {
    return null;
  }
  const a = (px * y2 - py * x2) / det;
  const b = (x1 * py - y1 * px) / det;
  if (Number.isInteger(a) && Number.isInteger(b)) {
    return [Math.trunc(a), Math.trunc(b)];
  }
  return null;
}

for (const clawMachine of clawMachines) {
  if (clawMachine.length >= 3) {
    const [x1, y1] = clawMachine[0];
    const [x2, y2] = clawMachine[1];
    const [px, py] = clawMachine[2];

    const solution = solveSystem(x1, y1, x2, y2, px, py);
    if (solution) {
      const [a, b] = solution;
      tokensOne += a * 3 + b;
    }

    const offset = 1e13;
    const solution2 = solveSystem(x1, y1, x2, y2, px + offset, py + offset);
    if (solution2) {
      const [a, b] = solution2;
      tokensTwo += a * 3 + b;
    }
  }
}

console.log(tokensOne);
console.log(tokensTwo);
