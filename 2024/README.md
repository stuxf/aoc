# 2024

First year doing AOC. Languages are split into multiple folders.

Something I wanted to restrict myself to this year was to not use libraries, and
keep everything within the standard library of each langauge.

I did all 25 days with Python, and then the first 20 days in Deno as well, as
Deno was running an event with free stickers \:D. I was originally intentending
to do other languages as well, but turns out writing more code does take more time.

- [Python](./Python/)

<!-- - [C++](./C++/) -->

- [Deno (TypeScript)](./Deno/)

<!-- - [Rust](./Rust/) -->
<!-- - [Go](./Go/) -->

## Problem Notes (⚠️⚠️⚠️ SPOILERS AHEAD ⚠️⚠️⚠️)

### Day 1

Fairly simple. You get two lists as input. Sort both of them and compare them
for part 1. Use a hashmap on the second list for part 2.

### Day 2

It's a little tricky to do the second part in $$O(N)$$

instead of $$O(N^2)$$

. First part is just making sure list is ascending/descending. For the second
part you just do the same, but if you run into a violation, you can remove the
element (do some array slicing) and run the same function as part one.

### Day 3

Fairly standard regex problem! I think if you can't use regex this problem gets
just a bit annoying.

### Day 4

First grid problem! I wasn't so used to handling grids, so this took me a bit
longer. Part 1 was a fairly simple just check all directions and check in bounds
to see if string matches `"XMAS"`. Part 2 was even easier, was just checking the
diagonals.

### Day 5

This one took quite a bit of code. Part one was pretty simple, given a bunch of
rules (dependencies), check if it satisfies them. Part two was to add the
dependencies, which I pretty much did recursively until it satisfied conditions.

It was technically more optimal in the worst case to implement with topological
sort rather than the recursion for part 2. I passed on it for a bit because the
implementation felt pretty painful. After revisiting the problem, turns out
Python has this built in! Makes it really simple! Unfortunately a bit harder to
implement in other languages...

### Day 6

This one ended up being pretty difficult to do optimally. Part one is fairly
simple, just simulate a bunch of things in a grid. Part two is more difficult, I
ended up initially with a very brute force approach, where I was inserting a
boulder along the route for each item in the route, and then checking to see if
we had a loop. There is a faster way to do this brute, by precomputing a jump
table, which I did not implement (yet).

### Day 7

This one was pretty fun! I somehow managed to fall on a pretty optimal recursion
solution on my first try, mostly by luck. I went around trying a bunch of other
implementations, which _should_ have been faster, but my initial solve seemed to
run faster on my machine for some reason. Quite happy with my speed!

But in essence, part one was just a 2^N brute. Part two makes it 3^N. You can
make it faster in both cases by applying some pruning, as well as recursing from
the back, which I did.

### Day 8

Pretty easy problem. Basically just translate the problem statement into code.
Ended up going back and optimizing it a bit by combining part one and part two
into a single pass of the array.

### Day 9

This problem was about disk fragmentation! Part one was a fairly simple brute.
Part two was a little bit more complicated, involved a lot of moving around of
different parts on the filesystem. Eventually the solution that seemed to me as
the most optimal was a bunch of different minheaps/priority queues. Definitely
felt like the difficulty was ramping up with part two of this problem. After
some more optimization, turns out the numbers are small enough that a very
minimal approach works best, using arrays and taking advantage of the fact that
the minimum is likely near the end of an array, instead of using a priority
queue.

### Day 10

Pretty easy DFS/BFS problem. I solved part two before I solved part one, which
seems to have been a pretty common occurence this year, judging from what other
people have been saying on Reddit. The twist between the two parts is the first
part is to track the number of approachable targets from all possible starting
points, (e.g the set of all possible targets), while part two you just add the
number of targets.

### Day 11

Feels pretty difficult at first when you read it. Key insight is that there are
actually not too many different stones, and to store a running count of them.
Allows for runtime to go pretty smoothly, and part 2 is just part one, but ran
many more times.

### Day 12

Part two was very tricky this year! There were a couple good solutions, I don't
think I implemented one, at least not on my first try. Basically you do a
sequence of floodfills on the whole grid. For part one, you find the perimeter,
for part two, you count the number of edges, which can be done by counting
corners. A union find seems more optimal, but isn't something I ultimately
implemented. My approach seems to run faster on my machine anyways.

### Day 13

Fairly standard linear algebra. I got gaslit into thinking z3 was part of the
standard library, so I initially solved with that. Went back and just solved the
systems of equations manually lol.

### Day 14

REALLY WEIRD PART TWO TODAY. Basically asks you to simualte a grid in part one,
and part two they tell you that at one frame it looks like a christmas tree, and
to find that frame. I ended up doing it by finding a frame with no overlaps, but
it turns out you can use Chinese Remainder Theorem as well.

### Day 15

Part one for this was a really standard sokoban problem. Part two had a bit of
an interesting twist, which ended up taking a while. Basically the map is twice
as wide, so boxes can now have branching pushes. Ended up doing a BFS to see
which posistions were moved, and checking if it was a valid move, before finally
moving.

### Day 16

Djikstra problem. Part one had a bit of a twist that rotations had a cost, so
what I did to address this was just had each rotation be a state. Part two, I
think it might be more optimal to modify djikstra to do a single pass and return
all optimal paths, but I ended up just doing a bfs for part two instead haha.

### Day 17

Part one is a fairly simple virtual machine. Just implementing it with three
registers, and follow the instructions. I'm a bit slow at implementation, so
this one took me a while. Part two ... was to reverse the virtual machine.
Really painful. Ended up doing it with some psuedo-bruting, and knowing that
each three bits corresponded to a change in one of the program numbers.

### Day 18

Easy BFS for part one. For part two, basically run the BFS a bunch more times. A
brute would've worked, but I did end up doing a binary search to be more
optimal. Technically a union-find would also work well here, but I haven't
really thought much about it.

### Day 19

Easy problem, at least once you break out the memoization and the dp. If you
don't, then I don't think you can run it in feasible time.

### Day 20

I ended up being the first one in the Deno discord to solve both parts! This was
a bit of a fun challenge. I took a while and bruted part one. Part two is a bit
trickier, and after a bit of thought, I ended up checking coordinate pairs of
manhattan distances after doing a bfs from the end to see which cheats would
save time, only comparing pairs. My solution thus ends up being relatively fast.

### Day 21

This one ended up being _really_ tricky. Seems like it might be the hardest
puzzle of the entire year. I think the key insight for this day was that the
keypads reset posistion to "A" every time, allowing you to iteratively bfs the
most optimal path for each layer. Using DP, this approach ends up being pretty
fast. Apparently there was an even better linear way to solve this problem, by
converting it into a matrix, and creating a lookup table, and using a series of
matrix multiplications. Alternatively, you could just make the lookup table, and
write a function that does a series of string replacements. I saw that some
people on reddit even generated their lookup tables manually, which is kind of
funny. Either way, generating the lookup table is essentially what DP is doing,
just with the added overhead of setting it up.

### Day 22

Funny problem to go through and solve. I was sick during this period of time,
starting day 21 actually, all the way until the end of AOC. But because I was
doing this problem late, I spent a bit more time reading through the storytext.
Very funny story involving banana monkey economics. Part 1 wasn't too hard, it's
about predicting RNG numbers, I originally was looking for a smart math way to
do it, but ended up just bruting it. With P2, turns out the brute was necessary,
and you just keep a dict that keeps track of all sequences throughout time.

### Day 23

There's no easy algorithm to solve this day's problem. Part one is to find all
cliques of size 3 in a graph, and part two is to find the maximal clique in the
graph. Turns out this is an NP problem, and there's an algorithm called
Bron-Kerbosch. I initially coded it this way, but while perusing the python
discord, I found another implementation, which I stole almost in its entirity
and put it into this repo. From @boxy. Not sure why, but it ran at about 10x my
Bron-Kerbosch implementation. It's really clean and really fast, probably the
first time I've been really blown away by someone's solution.

### Day 24

Part one wasn't too bad, part two was really hard lol. I know a lot of people
ended up solving part two by hand for this day. I was a bit confused how to do
so programatically, so I ended up taking u/LxsterGames solution from reddit.

So Part 2 is essentially simulating a ripple carry adder, and we can identify
the wrong logic gates by knowing a bit about how they work. We can use that to
identify some obviously wrong gates, and then identify the rest by comparing
the output of our circuit to what we expect

### Day 25

Fairly easy day, just check to see if there's overlap. Glad to be done. Happy
holidays!
