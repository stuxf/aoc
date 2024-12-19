const data = (await Deno.readTextFile("../inputs/03.txt")).split("\n").join("");

const sum1 = [...data.matchAll(/mul\((\d+),(\d+)\)/g)]
    .reduce((sum, [_, a, b]) => sum + (Number(a) * Number(b)), 0);

console.log(sum1);

let enabled = true;

const sum2 = [...data.matchAll(/mul\((\d+),(\d+)\)|do\(\)|don't\(\)/g)]
    .reduce((sum, [m, a, b]) => {
        if (m === "do()") return enabled = true, sum;
        if (m === "don't()") return enabled = false, sum;
        return enabled ? sum + (Number(a) + Number(b)) : sum;
    }, 0);

console.log(sum2);
