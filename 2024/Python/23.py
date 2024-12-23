from collections import defaultdict
data = open("../inputs/23.txt").read().splitlines()

connections = defaultdict(set)
nodes = set()

for l in data: 
    a, b = sorted(l.split("-"))
    connections[a] |= {b}
    nodes |= {a, b}

def get_cliques(subset): 
    res = {()}
    for node in subset:
        res |= {(node,) + k for k in get_cliques(subset & connections[node])}
    return res

cliques = get_cliques(nodes)

print(len([c for c in cliques if len(c) == 3 and any(n[0] == "t" for n in c)]))
print(",".join(max(cliques, key = len)))
