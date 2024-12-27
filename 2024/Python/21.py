from functools import cache
from itertools import permutations
codes = open("../inputs/21.txt").read().splitlines()


numpad = {
    "7": (0, 0),
    "8": (0, 1),
    "9": (0, 2),
    "4": (1, 0),
    "5": (1, 1),
    "6": (1, 2),
    "1": (2, 0),
    "2": (2, 1),
    "3": (2, 2),
    "_": (3, 0),
    "0": (3, 1),
    "A": (3, 2),
}

dirpad = {
    "_": (0, 0),
    "^": (0, 1),
    "A": (0, 2),
    "<": (1, 0),
    "v": (1, 1),
    ">": (1, 2),
}

numpad.update({v: k for k, v in numpad.items()})
dirpad.update({v: k for k, v in dirpad.items()})


def step(start, end, keypad):
    init_y, init_x = start
    final_y, final_x = end
    dy, dx = final_y - init_y, final_x - init_x

    vert = "v" * dy + "^" * -dy
    horiz = ">" * dx + "<" * -dx
    
    moves = vert + horiz
    valid_paths = []
    
    for path in permutations(moves):
        current = start
        valid = True
        
        for move in path:
            if move == "v":
                current = (current[0] + 1, current[1])
            elif move == "^":
                current = (current[0] - 1, current[1])
            elif move == ">":
                current = (current[0], current[1] + 1)
            elif move == "<":
                current = (current[0], current[1] - 1)
                
            if current in keypad and keypad[current] == "_":
                valid = False
                break
                
        if valid:
            valid_paths.append("".join(path) + "A")

    return valid_paths
            

@cache
def shortest_code(code, num_nums, num_dirs):
    start = "A"
    keypresses = 0

    if num_nums != 0:
        keypad = numpad
        new_nums = num_nums - 1
        new_dirs = num_dirs
    elif num_dirs != 0:
        keypad = dirpad
        new_nums = num_nums
        new_dirs = num_dirs - 1
    else:
        return len(code)

    curr_pos = keypad[start]

    for char in code:
        next_pos = keypad[char]
        new_codes = step(curr_pos, next_pos, keypad)
        keypresses += min(shortest_code(new_code, new_nums, new_dirs) for new_code in new_codes)
        curr_pos = next_pos

    return keypresses


print(sum(int(code[:-1]) * shortest_code(code, 1, 2) for code in codes))
print(sum(int(code[:-1]) * shortest_code(code, 1, 25) for code in codes))
