#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  vector<string> grid;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int rows = sz(grid), cols = sz(grid[0]);
  int dr[] = {0, 1, 0, -1};
  int dc[] = {1, 0, -1, 0};

  auto count = [&](int r, int c, int dir) {
    set<tuple<int, int, int>> seen;
    set<pair<int, int>> tiles;
    function<void(int, int, int)> dfs = [&](int r, int c, int dir) {
      if (r < 0 || r >= rows || c < 0 || c >= cols || seen.count({r, c, dir})) {
        return;
      }
      seen.insert({r, c, dir});
      tiles.insert({r, c});
      char cell = grid[r][c];
      if (cell == '.' || (cell == '-' && dir % 2 == 0) ||
          (cell == '|' && dir % 2 == 1)) {
        dfs(r + dr[dir], c + dc[dir], dir);
      } else if (cell == '/') {
        dfs(r + dr[3 - dir], c + dc[3 - dir], 3 - dir);
      } else if (cell == '\\') {
        dfs(r + dr[dir ^ 1], c + dc[dir ^ 1], dir ^ 1);
      } else if (cell == '-') {
        dfs(r, c - 1, 2);
        dfs(r, c + 1, 0);
      } else {
        dfs(r - 1, c, 3);
        dfs(r + 1, c, 1);
      }
    };
    dfs(r, c, dir);
    return sz(tiles);
  };

  part_one = count(0, 0, 0);

  rep(c, 0, cols) {
    part_two = max(part_two, (ll)count(0, c, 1));
    part_two = max(part_two, (ll)count(rows - 1, c, 3));
  }

  rep(r, 0, rows) {
    part_two = max(part_two, (ll)count(r, 0, 0));
    part_two = max(part_two, (ll)count(r, cols - 1, 2));
  }

  cout << part_one << endl;
  cout << part_two << endl;
}
