const data = (await Deno.readTextFile("../inputs/12.txt")).split("\n");
const H = data.length, W = data[0].length;
const dydx = [[0, 1], [1, 0], [-1, 0], [0, -1]];

const inBounds = (y: number, x: number) => 0 <= x && x < W && 0 <= y && y < H;

const searchAlg = (y: number, x: number) => {
    const repItem = data[y][x];
    const region = new Set<string>([`${y},${x}`]);
    const search = [[y, x]];
    while (search.length) {
        const [newY, newX] = search.pop()!;
        dydx.filter(([dy, dx]) =>
            inBounds(newY + dy, newX + dx) &&
            data[newY + dy][newX + dx] === repItem &&
            !region.has(`${newY + dy},${newX + dx}`)
        ).forEach(([dy, dx]) => {
            region.add(`${newY + dy},${newX + dx}`);
            search.push([newY + dy, newX + dx]);
        });
    }
    return region;
};

const findPerimeter = (region: Set<string>) =>
    [...region].reduce((perimeter, coord) => {
        const [y, x] = coord.split(",").map(Number);
        return perimeter +
            dydx.filter(([dy, dx]) => !region.has(`${y + dy},${x + dx}`))
                .length;
    }, 0);

const findSides = (region: Set<string>) =>
    [...region].reduce((corners, coord) => {
        const [y, x] = coord.split(",").map(Number);
        const cornerChecks = [[[0, 1], [1, 0]], [[0, 1], [-1, 0]], [[0, -1], [
            -1,
            0,
        ]], [[0, -1], [1, 0]]];
        const repItem = data[y][x];
        return corners + cornerChecks.filter(([[dy1, dx1], [dy2, dx2]]) => {
            const pos1: [number, number] = [y + dy1, x + dx1],
                pos2: [number, number] = [y + dy2, x + dx2];
            const cornerPos: [number, number] = [y + dy1 + dy2, x + dx1 + dx2];
            const isOuter =
                (!inBounds(...pos1) || data[pos1[0]][pos1[1]] !== repItem) &&
                (!inBounds(...pos2) || data[pos2[0]][pos2[1]] !== repItem);
            const isInner = inBounds(...pos1) &&
                data[pos1[0]][pos1[1]] === repItem &&
                inBounds(...pos2) && data[pos2[0]][pos2[1]] === repItem &&
                (!inBounds(...cornerPos) ||
                    data[cornerPos[0]][cornerPos[1]] !== repItem);
            return isOuter || isInner;
        }).length;
    }, 0);

let [pricesOne, pricesTwo] = [0, 0];
const visited = new Set<string>();

data.forEach((line, y) =>
    line.split("").forEach((_, x) => {
        if (!visited.has(`${y},${x}`)) {
            const region = searchAlg(y, x);
            region.forEach((coord) => visited.add(coord));
            const [area, perimeter, sides] = [
                region.size,
                findPerimeter(region),
                findSides(region),
            ];
            pricesOne += area * perimeter;
            pricesTwo += area * sides;
        }
    })
);

console.log(pricesOne);
console.log(pricesTwo);
