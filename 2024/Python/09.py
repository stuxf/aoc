data = open("../inputs/09.txt").read().strip()
disk = [int(b) for b in data]

def part1(disk):
    left = 0
    right = len(disk) - 2 + len(disk) % 2
    needed = disk[right]
    block = 0
    checksum = 0

    while left < right:
        id = left // 2
        extra = block * disk[left] + (disk[left] * (disk[left] - 1)) // 2
        checksum += id * extra
        block += disk[left]
        
        available = disk[left + 1]
        left += 2
        
        while available > 0:
            if needed == 0:
                if left == right:
                    break
                right -= 2
                needed = disk[right]
            
            size = min(needed, available)
            id = right // 2
            extra = block * size + (size * (size - 1)) // 2
            checksum += id * extra
            block += size
            available -= size
            needed -= size

    if needed > 0:
        id = right // 2
        extra = block * needed + (needed * (needed - 1)) // 2
        checksum += id * extra

    return checksum

def part2(disk):
    block = 0
    checksum = 0
    free = [[] for _ in range(10)]

    for idx, size in enumerate(disk):
        if idx % 2 == 1 and size > 0:
            free[size].append(block)
        block += size

    for blocks in free:
        blocks.append(block)
        blocks.reverse()

    for idx in range(len(disk) - 1, -1, -1):
        size = disk[idx]
        block -= size
        
        if idx % 2 == 1:
            continue
        
        next_block = block
        next_size = None
        
        for i in range(size, len(free)):
            if free[i] and free[i][-1] < next_block:
                next_block = free[i][-1]
                next_size = i
        
        id = idx // 2
        extra = next_block * size + (size * (size - 1)) // 2
        checksum += id * extra
        
        if next_size is not None:
            free[next_size].pop()
            remaining = next_size - size
            if remaining > 0:
                new_block = next_block + size
                free[remaining].append(new_block)
                free[remaining].sort(reverse=True)

    return checksum

print(part1(disk))
print(part2(disk))