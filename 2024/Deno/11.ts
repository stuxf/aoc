const data: number[] = (await Deno.readTextFile("../inputs/11.txt"))
    .split("\n")[0].split(" ").map(Number);

let stones: Record<number, number> = {};

for (const stone of data) {
    stones[stone] = (stones[stone] || 0) + 1;
}

function blink(stones: Record<number, number>): Record<number, number> {
    const newStones: Record<number, number> = {};
    for (const stone in stones) {
        const count = stones[stone];
        const stoneNum = Number(stone);
        const stoneL = stone.length;
        if (stoneNum === 0) {
            newStones[1] = (newStones[1] || 0) + count;
        } else if (stoneL % 2 === 0) {
            newStones[Number(stone.substring(0, stoneL / 2))] =
                (newStones[Number(stone.substring(0, stoneL / 2))] || 0) +
                count;
            newStones[Number(stone.substring(stoneL / 2))] =
                (newStones[Number(stone.substring(stoneL / 2))] || 0) + count;
        } else {
            newStones[stoneNum * 2024] = (newStones[stoneNum * 2024] || 0) +
                count;
        }
    }
    return newStones;
}

for (let blinks = 0; blinks < 75; blinks++) {
    if (blinks === 25) {
        console.log(Object.values(stones).reduce((a, b) => a + b, 0));
    }
    stones = blink(stones);
}

console.log(Object.values(stones).reduce((a, b) => a + b, 0));
