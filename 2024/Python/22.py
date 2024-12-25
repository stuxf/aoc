from itertools import pairwise, islice
from collections import defaultdict, deque

data = list(map(int, open("../inputs/22.txt").read().splitlines()))

PRUNE_AND = 0xFFFFFF
NUM_RNDS = 2000


def brute_secret(initial_secret):
    secrets = [initial_secret]
    secret = initial_secret
    for _ in range(NUM_RNDS):
        secret ^= secret << 6 & 0xFFFFFF
        secret ^= secret >> 5 & 0xFFFFFF
        secret ^= secret << 11 & 0xFFFFFF
        secrets.append(secret)
    return secrets


def sliding_window(iterable, n):
    it = iter(iterable)
    d = deque(islice(it, n), maxlen=n)
    yield tuple(d)
    for x in it:
        d.append(x)
        yield tuple(d)


secret_sum = 0
bananas_dict = defaultdict(int)
for i_sec in data:
    secs = brute_secret(i_sec)
    secret_sum += secs[NUM_RNDS]
    diffs = [a % 10 - b % 10 for a, b in pairwise(secs)]

    seen = set()

    for i, seq in enumerate(sliding_window(diffs, 4)):
        if seq not in seen:
            bananas_dict[seq] += secs[i+4] % 10
            seen.add(seq)

print(secret_sum)
print(max(bananas_dict.values()))
