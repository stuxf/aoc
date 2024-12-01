const data = (await Deno.readTextFile("input")).trim().split("\n");

const left: number[] = [];
const right: number[] = [];

for (const line of data) {
    const [l_id, r_id] = line.split(/\s+/).map(Number);
    left.push(l_id);
    right.push(r_id);
}

left.sort((a, b) => a - b);
right.sort((a, b) => a - b);

const distance = left.reduce((sum, l_id, i) => sum + Math.abs(l_id - right[i]), 0);

console.log(distance);

const id_ctr = new Map<number, number>();

for (const r_id of right) {
    id_ctr.set(r_id,(id_ctr.get(r_id) || 0) + 1);
}

const similarity = left.reduce((sum, l_id) => sum + l_id * (id_ctr.get(l_id) || 0), 0);

console.log(similarity)