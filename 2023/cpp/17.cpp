#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

ll solve(const vector<string> &grid, int min_steps = 1, int max_steps = 3) {
  int rows = grid.size(), cols = grid[0].size();

  priority_queue<tuple<int, int, int, int, int>,
                 vector<tuple<int, int, int, int, int>>, greater<>>
      pq;

  set<tuple<int, int, int, int>> visited;

  pq.push({0, 0, 0, -1, 0});

  while (!pq.empty()) {
    auto [heat, r, c, dir, steps] = pq.top();
    pq.pop();

    if (r == rows - 1 && c == cols - 1 && steps >= min_steps) {
      return heat;
    }

    if (!visited.insert({r, c, dir, steps}).second) {
      continue;
    }

    if (dir != -1 && steps < max_steps) {
      int nr = r + dr[dir];
      int nc = c + dc[dir];
      if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
        pq.push({heat + (grid[nr][nc] - '0'), nr, nc, dir, steps + 1});
      }
    }

    if (dir == -1 || steps >= min_steps) {
      for (int next_dir = 0; next_dir < 4; ++next_dir) {
        if (dir != -1 && (next_dir == dir || next_dir == (dir + 2) % 4)) {
          continue;
        }
        if (dir == -1 && (next_dir == 2 || next_dir == 3)) {
          continue;
        }

        int nr = r + dr[next_dir];
        int nc = c + dc[next_dir];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
          pq.push({heat + (grid[nr][nc] - '0'), nr, nc, next_dir, 1});
        }
      }
    }
  }
  return -1;
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  vector<string> grid;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  part_one = solve(grid);
  part_two = solve(grid, 4, 10);

  cout << part_one << endl;
  cout << part_two << endl;
}
