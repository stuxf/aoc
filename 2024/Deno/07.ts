const data = (await Deno.readTextFile("../inputs/07.txt")).trim().split("\n");

function allValid(arrNums: number[], res: number): number[] {
    if (arrNums.length === 1) return [arrNums[0]];
    const first = arrNums[0];
    return allValid(arrNums.slice(1), res).flatMap((num) => {
        const sum = first + num, product = first * num;
        return [sum, product].filter((x) => x <= res);
    });
}

function allValidTwo(arrNums: number[], res: number): number[] {
    if (arrNums.length === 1) return [arrNums[0]];
    const first = arrNums[0];
    const magnitude = 10 ** (Math.floor(Math.log10(first)) + 1);
    return allValidTwo(arrNums.slice(1), res).flatMap((num) => {
        const sum = first + num,
            product = first * num,
            concat = num * magnitude + first;
        return [sum, product, concat].filter((x) => x <= res);
    });
}

let [numValid, numValidTolerances] = [0, 0];

for (const line of data) {
    const [a, b] = line.split(":");
    const target = Number(a);
    const numbers = b.trim().split(" ").map(Number).reverse();

    if (allValid(numbers, target).includes(target)) numValid += target;
    else if (allValidTwo(numbers, target).includes(target)) {
        numValidTolerances += target;
    }
}

console.log(numValid);
console.log(numValidTolerances);
