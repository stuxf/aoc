const data = (await Deno.readTextFile("../inputs/20.txt")).split("\n");

const grid = new Map<string, boolean>();
let startPos: [number, number] = [0, 0];

for (let y = 0; y < data.length; y++) {
    for (let x = 0; x < data[y].length; x++) {
        const pos: [number, number] = [y, x];
        if (data[y][x] === "S") startPos = pos;
        grid.set(`${pos[0]},${pos[1]}`, data[y][x] === "#");
    }
}

const dydx = [[0, 1], [0, -1], [1, 0], [-1, 0]];
const manhattan = (p1: [number, number], p2: [number, number]): number =>
    Math.abs(p1[0] - p2[0]) + Math.abs(p1[1] - p2[1]);

const visited = new Map<string, number>([[`${startPos[0]},${startPos[1]}`, 0]]);
const q: [[number, number], number][] = [[startPos, 0]];

for (let i = 0; i < q.length; i++) {
    const [pos, cost] = q[i];
    const [y, x] = pos;
    for (const [dy, dx] of dydx) {
        const newPos: [number, number] = [y + dy, x + dx];
        if (
            !grid.get(`${newPos[0]},${newPos[1]}`) &&
            !visited.has(`${newPos[0]},${newPos[1]}`)
        ) {
            visited.set(`${newPos[0]},${newPos[1]}`, cost + 1);
            q.push([newPos, cost + 1]);
        }
    }
}

const visitedArr: [[number, number], number][] = Array.from(
    visited,
    ([posStr, cost]) => [
        posStr.split(",").map(Number) as [number, number],
        cost,
    ],
);

let part1 = 0;
let part2 = 0;

for (let i = 0; i < visitedArr.length; i++) {
    const [pos1, cost1] = visitedArr[i];
    for (let j = i + 1; j < visitedArr.length; j++) {
        const [pos2, cost2] = visitedArr[j];
        const mh = manhattan(pos1, pos2);
        if (mh <= 20 && Math.abs(cost2 - cost1) - mh >= 100) {
            if (mh === 2) part1++;
            part2++;
        }
    }
}

console.log(part1);
console.log(part2);
