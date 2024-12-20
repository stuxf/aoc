const data: number[][] = Deno.readTextFileSync("../inputs/10.txt")
    .trim()
    .split("\n")
    .map((line) => line.split("").map((c) => (c === "." ? -1 : Number(c))));

const H = data.length;
const W = data[0].length;

const dydx: [number, number][] = [[0, 1], [1, 0], [-1, 0], [0, -1]];

function validCoord(y: number, x: number): boolean {
    return 0 <= y && y < H && 0 <= x && x < W;
}

const starts: [number, number][] = [];
for (let y = 0; y < H; y++) {
    for (let x = 0; x < W; x++) {
        if (data[y][x] === 0) {
            starts.push([y, x]);
        }
    }
}

function dfs(
    initial: [number, number],
    part2 = false,
    visited: Set<string> | null = null,
): number {
    if (visited === null || part2) {
        visited = new Set();
    }
    const key = `${initial[0]},${initial[1]}`;
    if (visited.has(key)) {
        return 0;
    }
    visited.add(key);
    const [y, x] = initial;
    const val = data[y][x];
    if (val === 9) {
        return 1;
    }
    let sum = 0;
    for (const [dy, dx] of dydx) {
        const [newY, newX] = [y + dy, x + dx];
        if (!validCoord(newY, newX) || data[newY][newX] === -1) {
            continue;
        }
        const newVal = data[newY][newX];
        if (newVal === val + 1) {
            sum += dfs([newY, newX], part2, visited);
        }
    }
    return sum;
}

let scores = 0;
let ratings = 0;

for (const init of starts) {
    scores += dfs(init);
    ratings += dfs(init, true);
}

console.log(scores);
console.log(ratings);
