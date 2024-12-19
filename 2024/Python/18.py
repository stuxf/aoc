from collections import deque

data = open("../inputs/18.txt").read().splitlines()

N = 70

dxdy = [(0, 1), (1, 0), (0, -1), (-1, 0)]

corrupted = [tuple(map(int, memory.split(","))) for memory in data]

start_pos = (0, 0)
end_pos = (N, N)


def is_valid(x, y, corrupted):
    return 0 <= x <= N and 0 <= y <= N and (x, y) not in corrupted


def bfs(corrupted):
    q = deque([(0, start_pos[0], start_pos[1])])

    visited = {start_pos}

    while q:
        steps, x, y = q.popleft()
        if (x, y) == end_pos:
            return steps
        for dx, dy in dxdy:
            nx, ny = x + dx, y + dy
            if is_valid(nx, ny, corrupted) and (nx, ny) not in visited:
                visited.add((nx, ny))
                q.append((steps + 1, nx, ny))
    return None


print(bfs(set(corrupted[:1024])))

low, high = 1024, len(corrupted)
while low < high:
    mid = (low + high) // 2
    if bfs(set(corrupted[:mid])) is None:
        high = mid
    else:
        low = mid + 1

print(",".join(str(num) for num in corrupted[low - 1]))
