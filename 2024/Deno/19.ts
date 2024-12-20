const [patternsStr, towelsStr] = (await Deno.readTextFile("../inputs/19.txt"))
  .split("\n\n");

const patterns = patternsStr.split(", ");
const towels = towelsStr.split("\n");

const memo = new Map<string, number>();

function possibleDesigns(towel: string): number {
  if (!towel) {
    return 1;
  }

  if (memo.has(towel)) {
    return memo.get(towel)!;
  }

  let options = 0;
  for (const pattern of patterns) {
    if (towel.startsWith(pattern)) {
      options += possibleDesigns(towel.slice(pattern.length));
    }
  }

  memo.set(towel, options);
  return options;
}

console.log(towels.filter((towel) => possibleDesigns(towel) > 0).length);
console.log(towels.reduce((sum, towel) => sum + possibleDesigns(towel), 0));
