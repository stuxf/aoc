const disk: number[] = (await Deno.readTextFile("../inputs/09.txt")).trim()
  .split("").map(Number);

function part1(disk: number[]): number {
  let left = 0;
  let right = disk.length - 2 + disk.length % 2;
  let needed = disk[right];
  let block = 0;
  let checksum = 0;

  while (left < right) {
    const id = Math.floor(left / 2);
    const extra = block * disk[left] +
      Math.floor((disk[left] * (disk[left] - 1)) / 2);
    checksum += id * extra;
    block += disk[left];

    let available = disk[left + 1];
    left += 2;

    while (available > 0) {
      if (needed === 0) {
        if (left === right) break;
        right -= 2;
        needed = disk[right];
      }

      const size = Math.min(needed, available);
      const id = Math.floor(right / 2);
      const extra = block * size + Math.floor((size * (size - 1)) / 2);
      checksum += id * extra;
      block += size;
      available -= size;
      needed -= size;
    }
  }

  if (needed > 0) {
    const id = Math.floor(right / 2);
    const extra = block * needed + Math.floor((needed * (needed - 1)) / 2);
    checksum += id * extra;
  }

  return checksum;
}

function part2(disk: number[]): number {
  let block = 0;
  let checksum = 0;
  const free: number[][] = Array(10).fill(null).map(() => []);

  for (let idx = 0; idx < disk.length; idx++) {
    const size = disk[idx];
    if (idx % 2 === 1 && size > 0) {
      free[size].push(block);
    }
    block += size;
  }

  for (const blocks of free) {
    blocks.push(block);
    blocks.reverse();
  }

  for (let idx = disk.length - 1; idx >= 0; idx--) {
    const size = disk[idx];
    block -= size;

    if (idx % 2 === 1) continue;

    let nextBlock = block;
    let nextSize: number | null = null;

    for (let i = size; i < free.length; i++) {
      if (free[i].length && free[i][free[i].length - 1] < nextBlock) {
        nextBlock = free[i][free[i].length - 1];
        nextSize = i;
      }
    }

    const id = Math.floor(idx / 2);
    const extra = nextBlock * size + Math.floor((size * (size - 1)) / 2);
    checksum += id * extra;

    if (nextSize !== null) {
      free[nextSize].pop();
      const remaining = nextSize - size;
      if (remaining > 0) {
        const newBlock = nextBlock + size;
        free[remaining].push(newBlock);
        free[remaining].sort((a, b) => b - a);
      }
    }
  }

  return checksum;
}

console.log(part1(disk));
console.log(part2(disk));
