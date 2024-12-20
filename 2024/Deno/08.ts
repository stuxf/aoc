const data = (await Deno.readTextFile("../inputs/08.txt")).trim().split("\n");
const [H, W] = [data.length, data[0].length];

const antennas = data.reduce((map, row, y) => {
    [...row].forEach((char, x) => {
        if (char !== ".") map.set(char, [...(map.get(char) || []), [y, x]]);
    });
    return map;
}, new Map<string, [number, number][]>());

function countAllAntinodes(
    antennas: Map<string, [number, number][]>,
): [number, number] {
    const basic = new Set<string>();
    const extended = new Set<string>();

    const addPoints = (y: number, x: number, dy: number, dx: number) => {
        let mult = 0;
        while (y >= 0 && y < H && x >= 0 && x < W) {
            const pos = `${y},${x}`;
            extended.add(pos);
            if (mult === 1) basic.add(pos);
            mult++;
            y += dy;
            x += dx;
        }
    };

    for (const points of antennas.values()) {
        for (let i = 0; i < points.length - 1; i++) {
            const [y1, x1] = points[i];
            for (const [y2, x2] of points.slice(i + 1)) {
                const [dy, dx] = [y2 - y1, x2 - x1];
                addPoints(y1, x1, -dy, -dx);
                addPoints(y2, x2, dy, dx);
            }
        }
    }

    return [basic.size, extended.size];
}

const [antinodes, antinodesExtended] = countAllAntinodes(antennas);
console.log(antinodes);
console.log(antinodesExtended);
