const reports = (await Deno.readTextFile("../inputs/02.txt")).trim().split("\n")
  .map((line) => line.split(/\s+/).map(Number));

const safe = (lvls: number[]): boolean => {
  if (lvls.length < 2) return true;

  const dir = Math.sign(lvls[1] - lvls[0]);

  for (let i = 1; i < lvls.length; i++) {
    const diff = lvls[i] - lvls[i - 1];
    if (diff * dir <= 0 || Math.abs(diff) > 3) return false;
  }
  return true;
};

const safeDamp = (lvls: number[]): boolean => {
  if (lvls.length < 2) return true;

  const dir = Math.sign(lvls[1] - lvls[0]);

  for (let i = 1; i < lvls.length; i++) {
    const diff = lvls[i] - lvls[i - 1];
    if (diff * dir <= 0 || Math.abs(diff) > 3) {
      return [-1, 0, 1].some((offset) => {
        const j = i + offset;
        return safe([...lvls.slice(0, j - 1), ...lvls.slice(j)]);
      });
    }
  }

  return true;
};
console.log(reports.filter(safe).length);
console.log(reports.filter(safeDamp).length);
