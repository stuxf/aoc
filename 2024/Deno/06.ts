const data = (await Deno.readTextFile("../inputs/06.txt")).trim().split("\n")
    .map((line) => line.split(""));

const H = data.length;
const W = data[0].length;

const start: [number, number] = (() => {
    for (let y = 0; y < H; y++) {
        for (let x = 0; x < W; x++) {
            if (data[y][x] === "^") return [y, x];
        }
    }
    return [0, 0];
})();

const dirs = [[1, 0], [0, -1], [-1, 0], [0, 1]];

function turn(d: number[]) {
    return dirs[
        (dirs.findIndex((dir) => dir[0] === d[0] && dir[1] === d[1]) + 1) % 4
    ];
}

function inBounds(y: number, x: number) {
    return 0 <= y && y < H && 0 <= x && x < W;
}

function walk() {
    const visited = new Set<string>();
    let [dy, dx] = [-1, 0];
    let [y, x] = start;
    while (true) {
        y += dy;
        x += dx;
        if (!inBounds(y, x)) {
            break;
        }
        if (data[y][x] === "#") {
            y -= dy;
            x -= dx;
            [dy, dx] = turn([dy, dx]);
        }
        visited.add(`${y},${x}`);
    }
    return visited;
}

function hasLoop(oY: number, oX: number, gridCopy: string[][]) {
    const visited = new Set<string>();
    let [dy, dx] = [-1, 0];
    let [y, x] = start;
    visited.add(`${y},${x},${dy},${dx}`);
    while (true) {
        y += dy;
        x += dx;
        if (visited.has(`${y},${x},${dy},${dx}`)) {
            return true;
        }
        if (!inBounds(y, x)) {
            return false;
        }
        if (gridCopy[y][x] === "#" || (y === oY && x === oX)) {
            y -= dy;
            x -= dx;
            [dy, dx] = turn([dy, dx]);
        }
        visited.add(`${y},${x},${dy},${dx}`);
    }
}

const path = walk();

console.log(path.size);

console.log(
    Array.from(path).reduce((acc, coord) => {
        const [oY, oX] = coord.split(",").map(Number);
        if (data[oY][oX] === ".") {
            return acc + (hasLoop(oY, oX, data.map((row) => [...row])) ? 1 : 0);
        }
        return acc;
    }, 0),
);
