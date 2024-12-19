const data = (await Deno.readTextFile("../inputs/04.txt")).trim().split("\n");

const dydx = [
    [-1, -1],
    [-1, 0],
    [-1, 1],
    [0, -1],
    [0, 1],
    [1, -1],
    [1, 0],
    [1, 1],
];

const diag = [[-1, -1], [-1, 1], [1, -1], [1, 1]];

const H = data.length;
const W = data[0].length;

let searchCount = 0;
let revisedSearchCount = 0;

for (let y = 0; y < H; y++) {
    for (let x = 0; x < W; x++) {
        if (y > 0 && y < H - 1 && x > 0 && x < W - 1 && data[y][x] === "A") {
            const corners = diag.map(([dy, dx]) => data[y + dy][x + dx]);
            if (
                corners.filter((c) => c === "M").length === 2 &&
                corners.filter((c) => c === "S").length === 2 &&
                corners[0] !== corners[3]
            ) {
                revisedSearchCount++;
            }
        }

        if (data[y][x] != "X") continue;

        for (const [dy, dx] of dydx) {
            const chars = ["X"];

            for (let d = 1; d < 4; d++) {
                const newY = y + dy * d;
                const newX = x + dx * d;
                if (!(0 <= newY && newY < H && 0 <= newX && newX < W)) {
                    break;
                }
                chars.push(data[newY][newX]);
            }
            if (chars.join("") === "XMAS") {
                searchCount++;
            }
        }
    }
}

console.log(searchCount);
console.log(revisedSearchCount);
