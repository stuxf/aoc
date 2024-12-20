const data = (await Deno.readTextFile("../inputs/15.txt")).split("\n\n")

const [grid, moves] = data

type Grid = string[][]
type Position = [number, number]
type Direction = [-1, 0] | [1, 0] | [0, -1] | [0, 1]

const gridArr: Grid = grid.split("\n").map(line => [...line])

const H = gridArr.length
const W = gridArr[0].length

const inBounds = (y: number, x: number): boolean => 
  0 <= y && y < H && 0 <= x && x < W

const movesStr = moves.replace(/\s/g, "")

const moveDirs: Record<string, Direction> = {
  "^": [-1, 0],
  ">": [0, 1],
  "<": [0, -1],
  "v": [1, 0]
}

let startPos: Position = [0, 0]
gridArr.forEach((line, y) => {
  line.forEach((item, x) => {
    if (item === "@") startPos = [y, x]
  })
})

const moveRobot = (grid: Grid, pos: Position, move: string): [Grid, Position] => {
  const [dy, dx] = moveDirs[move]
  const [rY, rX] = pos

  const dirItems: string[] = []
  let i = 0
  while (true) {
    dirItems.push(grid[rY + i * dy][rX + i * dx])
    if (dirItems[dirItems.length - 1] === "#" || grid[rY + i * dy][rX + i * dx] === ".") {
      break
    }
    i++
  }

  if (dirItems[dirItems.length - 1] === "#") {
    return [grid, pos]
  }

  for (let j = 0; j < dirItems.length; j++) {
    grid[rY + j * dy][rX + j * dx] = dirItems[(j - 1 + dirItems.length) % dirItems.length]
  }

  return [grid, [rY + dy, rX + dx]]
}

let pos = startPos
for (const move of movesStr) {
  [gridArr, pos] = moveRobot(gridArr, pos, move)
}

console.log(
  gridArr.reduce((sum, line, y) => 
    sum + line.reduce((rowSum, item, x) => 
      rowSum + (item === "O" ? 100 * y + x : 0), 0), 0)
)

const wideMap: Record<string, [string, string]> = {
  "#": ["#", "#"],
  ".": [".", "."],
  "O": ["[", "]"],
  "@": ["@", "."]
}

const newGrid: string[][] = data[0].split("\n").map(line => 
  [...line].flatMap(char => wideMap[char]))

startPos = [0, 0]
newGrid.forEach((line, y) => {
  line.forEach((item, x) => {
    if (item === "@") startPos = [y, x]
  })
})

pos = startPos

const horiz: [number, number][] = [[0, 1], [0, -1]]

const search = (grid: string[][], pos: Position, move: string): [boolean, Set<Position>] => {
  const [dy, dx] = moveDirs[move]
  const [y, x] = pos
  const visited = new Set<string>()

  const dfs = (y: number, x: number): [boolean, Set<Position>] => {
    if (!(0 <= y && y < grid.length && 0 <= x && x < grid[0].length)) {
      return [true, new Set()]
    }
    if (grid[y][x] === "#") {
      return [true, new Set()]
    }
    if (grid[y][x] === ".") {
      return [false, new Set([[y, x]])]
    }
    if (visited.has(`${y},${x}`)) {
      return [false, new Set()]
    }

    visited.add(`${y},${x}`)
    const toMove = new Set<Position>()

    if (horiz.some(([hdy, hdx]) => hdy === dy && hdx === dx)) {
      const [stopped, positions] = dfs(y + dy, x + dx)
      if (stopped) {
        return [true, new Set()]
      }
      toMove.add([y, x])
      positions.forEach(pos => toMove.add(pos))
    } else {
      if (grid[y][x] === "[") {
        const [stopped, rightPos] = dfs(y, x + 1)
        if (stopped) {
          return [true, new Set()]
        }
        rightPos.forEach(pos => toMove.add(pos))
      } else if (grid[y][x] === "]") {
        const [stopped, leftPos] = dfs(y, x - 1)
        if (stopped) {
          return [true, new Set()]
        }
        leftPos.forEach(pos => toMove.add(pos))
      }

      const [stopped, nextPos] = dfs(y + dy, x)
      if (stopped) {
        return [true, new Set()]
      }

      toMove.add([y, x])
      nextPos.forEach(pos => toMove.add(pos))
    }

    return [false, toMove]
  }

  const [nextY, nextX] = [y + dy, x + dx]
  const [stopped, positions] = dfs(nextY, nextX)
  if (stopped) {
    return [false, new Set()]
  }
  return [true, positions]
}

const moveTwo = (grid: string[][], pos: Position, move: string): [string[][], Position] => {
  const [dy, dx] = moveDirs[move]
  const [ry, rx] = pos
  const [canMove, toMove] = search(grid, pos, move)
  if (!canMove) {
    return [grid, pos]
  }

  const positions = Array.from(toMove)
  if (dx > 0) {
    positions.sort(([y1, x1], [y2, x2]) => x2 - x1)
  } else if (dx < 0) {
    positions.sort(([y1, x1], [y2, x2]) => x1 - x2)
  } else if (dy > 0) {
    positions.sort(([y1, x1], [y2, x2]) => y2 - y1)
  } else {
    positions.sort(([y1, x1], [y2, x2]) => y1 - y2)
  }

  positions.forEach(([y, x]) => {
    if (toMove.has([y - dy, x - dx] as Position)) {
      grid[y][x] = grid[y - dy][x - dx]
    } else {
      grid[y][x] = "."
    }
  })

  grid[ry][rx] = "."
  grid[ry + dy][rx + dx] = "@"

  return [grid, [ry + dy, rx + dx]]
}

for (const move of movesStr) {
  [newGrid, pos] = moveTwo(newGrid, pos, move)
}

console.log(
  newGrid.reduce((sum, line, y) => 
    sum + line.reduce((rowSum, item, x) => 
      rowSum + (item === "[" ? 100 * y + x : 0), 0), 0)
)