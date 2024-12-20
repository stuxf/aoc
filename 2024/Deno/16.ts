const data = (await Deno.readTextFile("../inputs/16.txt")).split("\n");

const dydx = [[0, 1], [1, 0], [0, -1], [-1, 0]];

const H = data.length;
const W = data[0].length;

const R_COST = 1000;
const M_COST = 1;

const rotate = (dir: number[], clockwise: boolean) => {
  const dir_idx = dydx.findIndex((d) => d[0] === dir[0] && d[1] === dir[1]);
  if (clockwise) {
    return dydx[(dir_idx + 1) % dydx.length];
  }
  return dydx[(dir_idx - 1 + dydx.length) % dydx.length];
};

let start_pos: number[] = [];
let end_pos: number[] = [];

for (let y = 0; y < H; y++) {
  for (let x = 0; x < W; x++) {
    if (data[y][x] === "S") {
      start_pos = [y, x];
    }
    if (data[y][x] === "E") {
      end_pos = [y, x];
    }
  }
}

const dijkstra = (
  grid: string[],
  start_pos: number[],
  start_dir = [0, 1],
) => {
  const distances = new Map<string, number>();
  const hash = (pos: number[], dir: number[]) =>
    `${pos[0]},${pos[1]},${dir[0]},${dir[1]}`;

  distances.set(hash(start_pos, start_dir), 0);

  const pq: [number, number[], number[]][] = [[0, start_pos, start_dir]];

  while (pq.length) {
    pq.sort((a, b) => a[0] - b[0]);
    const [cur_distance, cur_pos, cur_dir] = pq.shift()!;

    const r_y = cur_pos[0];
    const r_x = cur_pos[1];
    const dy = cur_dir[0];
    const dx = cur_dir[1];

    if (
      cur_distance > (distances.get(hash(cur_pos, cur_dir)) ?? Infinity)
    ) {
      continue;
    }

    if (
      r_y + dy >= 0 && r_y + dy < H && r_x + dx >= 0 && r_x + dx < W &&
      grid[r_y + dy][r_x + dx] !== "#"
    ) {
      const distance = cur_distance + M_COST;
      if (
        distance <
          (distances.get(hash([r_y + dy, r_x + dx], cur_dir)) ??
            Infinity)
      ) {
        distances.set(hash([r_y + dy, r_x + dx], cur_dir), distance);
        pq.push([distance, [r_y + dy, r_x + dx], cur_dir]);
      }
    }

    for (const clockwise of [true, false]) {
      const distance = cur_distance + R_COST;
      const new_dir = rotate(cur_dir, clockwise);
      if (
        distance < (distances.get(hash(cur_pos, new_dir)) ?? Infinity)
      ) {
        distances.set(hash(cur_pos, new_dir), distance);
        pq.push([distance, cur_pos, new_dir]);
      }
    }
  }

  return distances;
};

const distances = dijkstra(data, start_pos);

console.log(
  Math.min(
    ...dydx.map((dir) =>
      distances.get(`${end_pos[0]},${end_pos[1]},${dir[0]},${dir[1]}`) ??
        Infinity
    ),
  ),
);

const paths = (distances: Map<string, number>, end_pos: number[]) => {
  const path_positions = new Set<string>();
  const end_distance = Math.min(
    ...dydx.map((dir) =>
      distances.get(`${end_pos[0]},${end_pos[1]},${dir[0]},${dir[1]}`) ??
        Infinity
    ),
  );
  const stack: [number[], number[], number][] = [];

  for (const dir of dydx) {
    const dist = distances.get(
      `${end_pos[0]},${end_pos[1]},${dir[0]},${dir[1]}`,
    );
    if (dist !== undefined && dist === end_distance) {
      stack.push([end_pos, dir, end_distance]);
    }
  }

  const hash = (pos: number[]) => `${pos[0]},${pos[1]}`;

  while (stack.length) {
    const [pos, cur_dir, dist] = stack.pop()!;

    path_positions.add(hash(pos));

    const y = pos[0];
    const x = pos[1];
    const dy = cur_dir[0];
    const dx = cur_dir[1];
    const p_y = y - dy;
    const p_x = x - dx;

    const prevDist = distances.get(
      `${p_y},${p_x},${cur_dir[0]},${cur_dir[1]}`,
    );
    if (prevDist !== undefined && prevDist + M_COST === dist) {
      stack.push([[p_y, p_x], cur_dir, prevDist]);
    }

    for (const clockwise of [true, false]) {
      const prev_dir = rotate(cur_dir, clockwise);
      const rotatedDist = distances.get(
        `${pos[0]},${pos[1]},${prev_dir[0]},${prev_dir[1]}`,
      );
      if (rotatedDist !== undefined && rotatedDist + R_COST === dist) {
        stack.push([pos, prev_dir, rotatedDist]);
      }
    }
  }

  return path_positions;
};

console.log(paths(distances, end_pos).size);
