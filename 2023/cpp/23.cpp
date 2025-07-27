#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)
vector<string> grid;
int rows, cols;
map<char, pair<int, int>> dir = {
    {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}, {'^', {-1, 0}}};

bool is_valid(int r, int c) {
  return r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != '#';
}

int dfs(vector<vector<pair<int, int>>> &graph, vector<bool> &seen, int goal,
        int curr) {
  if (curr == goal)
    return 0;
  int max_dist = -1;
  for (auto [next, d] : graph[curr]) {
    if (!seen[next]) {
      seen[next] = true;
      int dist = dfs(graph, seen, goal, next);
      if (dist != -1) {
        max_dist = max(max_dist, d + dist);
      }
      seen[next] = false;
    }
  }
  return max_dist;
}

int solve(bool part2) {
  map<pair<int, int>, vector<tuple<int, int, int>>> graph;

  rep(r, 0, rows) {
    rep(c, 0, cols) {
      if (grid[r][c] == '#')
        continue;
      vector<pair<int, int>> neighbors;
      if (part2 || grid[r][c] == '.') {
        trav(d, dir) { neighbors.push_back(d.second); }
      } else {
        neighbors.push_back(dir[grid[r][c]]);
      }
      for (auto [dr, dc] : neighbors) {
        int nr = r + dr, nc = c + dc;
        if (is_valid(nr, nc)) {
          graph[{r, c}].push_back({nr, nc, 1});
        }
      }
    }
  }

  vector<pair<int, int>> corridors;

  for (auto &[pos, neighbors] : graph) {
    if (sz(neighbors) == 2) {
      corridors.push_back(pos);
    }
  }

  for (auto [r, c] : corridors) {
    auto neighbors = graph[{r, c}];
    graph.erase({r, c});
    auto [r1, c1, d1] = neighbors[0];
    auto [r2, c2, d2] = neighbors[1];
    auto &n1 = graph[{r1, c1}];
    rep(i, 0, sz(n1)) {
      if (get<0>(n1[i]) == r && get<1>(n1[i]) == c) {
        n1[i] = {r2, c2, d1 + d2};
        break;
      }
    }

    auto &n2 = graph[{r2, c2}];
    rep(i, 0, sz(n2)) {
      if (get<0>(n2[i]) == r && get<1>(n2[i]) == c) {
        n2[i] = {r1, c1, d1 + d2};
        break;
      }
    }
  }

  map<pair<int, int>, int> indexes;
  int idx = 0;

  for (auto &[pos, _] : graph) {
    indexes[pos] = idx++;
  }

  vector<vector<pair<int, int>>> idx_graph(idx);
  for (auto &[pos, neighbors] : graph) {
    int pos_idx = indexes[pos];
    for (auto [r, c, d] : neighbors) {
      idx_graph[pos_idx].push_back({indexes[{r, c}], d});
    }
  }

  int start_idx = indexes[{0, 1}];
  int goal_idx = indexes[{rows - 1, cols - 2}];
  vector<bool> seen(idx, false);
  seen[start_idx] = true;

  return dfs(idx_graph, seen, goal_idx, start_idx);
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  while (getline(cin, line)) {
    grid.push_back(line);
  }

  rows = sz(grid), cols = sz(grid[0]);

  part_one = solve(false);
  part_two = solve(true);

  cout << part_one << endl;
  cout << part_two << endl;
}
