const data = (await Deno.readTextFile("../inputs/14.txt"))
  .split("\n")
  .filter(line => line.length > 0);

const W = 101;
const H = 103;

const quadrants = [0, 0, 0, 0, 0];

const quadrantId = (coords: number[]): number => {
  const [x, y] = coords;
  if (y > H / 2 && x > W / 2) return 1;
  if (y > H / 2 && x < W / 2) return 2;
  if (y < H / 2 && x > W / 2) return 3;
  if (y < H / 2 && x < W / 2) return 4;
  return 0;
};

const simulateRobot = (p: number[], v: number[], steps = 100): number[] => {
  const [px, py] = p;
  const [vx, vy] = v;
  return [
    ((px + steps * vx) % W + W) % W,
    ((py + steps * vy) % H + H) % H
  ];
};

const robots = data.map(line => {
  const [p, v] = line.split(" ");
  return [
    p.slice(2).split(",").map(Number),
    v.slice(2).split(",").map(Number)
  ];
});

robots.forEach(([p, v]) => {
  quadrants[quadrantId(simulateRobot(p, v))]++;
});

console.log(quadrants.slice(1).reduce((a, b) => a * b));

for (let i = 0; i < 10000; i++) {
  const grid = new Map<string, number>();
  
  robots.forEach(([p, v]) => {
    const pos = simulateRobot(p, v, i);
    const key = pos.join(",");
    grid.set(key, (grid.get(key) || 0) + 1);
  });

  if ([...grid.values()].every(count => count === 1)) {
    console.log(i);
    break;
  }
}