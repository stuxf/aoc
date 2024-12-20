const data = (await Deno.readTextFile("../inputs/18.txt")).split("\n");

const N = 70;

const dxdy = [[0, 1], [1, 0], [0, -1], [-1, 0]];

const corrupted: [number, number][] = data.map((memory) =>
  memory.split(",").map(Number) as [number, number]
);

const start_pos = [0, 0];
const end_pos = [N, N];

const isValid = (x: number, y: number, corrupted: Set<string>): boolean =>
  0 <= x && x <= N && 0 <= y && y <= N && !corrupted.has(`${x},${y}`);

const bfs = (corrupted: Set<string>): number | null => {
  const q: [number, number, number][] = [[0, start_pos[0], start_pos[1]]];
  const visited = new Set<string>([`${start_pos[0]},${start_pos[1]}`]);

  while (q.length > 0) {
    const [steps, x, y] = q.shift()!;
    if (x === end_pos[0] && y === end_pos[1]) {
      return steps;
    }
    for (const [dx, dy] of dxdy) {
      const nx = x + dx;
      const ny = y + dy;
      if (isValid(nx, ny, corrupted) && !visited.has(`${nx},${ny}`)) {
        visited.add(`${nx},${ny}`);
        q.push([steps + 1, nx, ny]);
      }
    }
  }
  return null;
};

console.log(
  bfs(new Set(corrupted.slice(0, 1024).map((p) => `${p[0]},${p[1]}`))),
);

let low = 1024;
let high = corrupted.length;
while (low < high) {
  const mid = Math.floor((low + high) / 2);
  if (
    bfs(new Set(corrupted.slice(0, mid).map((p) => `${p[0]},${p[1]}`))) ===
      null
  ) {
    high = mid;
  } else {
    low = mid + 1;
  }
}

console.log(corrupted[low - 1].join(","));
