const data = await Deno.readTextFile("../inputs/05.txt");
const [graphData, updateData] = data.trim().split("\n\n");

const graph = new Map<number, Set<number>>();
graphData.split("\n").forEach((line) => {
    const [first, next] = line.split("|").map(Number);
    if (!graph.has(next)) graph.set(next, new Set());
    graph.get(next)!.add(first);
});

const updates = updateData.split("\n").map((line) =>
    line.split(",").map(Number)
);

const isOrdered = (sequence: number[]) =>
    !sequence.some((item, i) =>
        [...(graph.get(item) || [])].some((dep) => sequence.indexOf(dep) > i)
    );

const topoSort = (deps: Map<number, Set<number>>, nodes: number[]) => {
    const sorted: number[] = [];
    const visited = new Set<number>();
    const dfs = (node: number) => {
        if (visited.has(node)) return;
        visited.add(node);
        deps.get(node)
            ?.forEach((dep) => nodes.includes(dep) && dfs(dep));
        sorted.push(node);
    };
    nodes.forEach((node) => dfs(node));
    return sorted.reverse();
};

const reorder = (sequence: number[]) =>
    topoSort(
        new Map(sequence.map((n) => [
            n,
            new Set(
                [...(graph.get(n) ?? [])].filter((d) => sequence.includes(d)),
            ),
        ])),
        sequence,
    );

let middleSum = 0;
let middleSumCorrected = 0;

updates.forEach((update) => {
    if (isOrdered(update)) {
        middleSum += update[Math.floor(update.length / 2)];
    } else {
        middleSumCorrected += reorder(update)[Math.floor(update.length / 2)];
    }
});

console.log(middleSum);
console.log(middleSumCorrected);
