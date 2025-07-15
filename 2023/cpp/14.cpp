#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

vector<string> tilt_north(const vector<string> &grid) {
  vector<string> new_grid = grid;
  int rows = sz(grid), cols = sz(grid[0]);

  rep(i, 0, rows) {
    rep(j, 0, cols) {
      if (new_grid[i][j] == 'O') {
        int target = i;
        while (target > 0 && new_grid[target - 1][j] == '.') {
          target--;
        }
        if (target != i) {
          new_grid[i][j] = '.';
          new_grid[target][j] = 'O';
        }
      }
    }
  }

  return new_grid;
}

vector<string> rotate_90(const vector<string> &grid) {
  int rows = sz(grid), cols = sz(grid[0]);
  vector<string> rotated(cols, string(rows, '.'));
  rep(i, 0, rows) {
    rep(j, 0, cols) { rotated[j][rows - 1 - i] = grid[i][j]; }
  }
  return rotated;
}

int total_load(const vector<string> &grid) {
  int rows = sz(grid);
  int total = 0;

  rep(i, 0, rows) {
    rep(j, 0, sz(grid[i])) {
      if (grid[i][j] == 'O') {
        total += rows - i;
      }
    }
  }

  return total;
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;
  vector<string> grid;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  vector<string> tilted_grid = tilt_north(grid);
  part_one = total_load(tilted_grid);

  map<vector<string>, int> seen;
  vector<string> current = grid;
  int cycle_num = 0;

  while (seen.find(current) == seen.end()) {
    seen[current] = cycle_num;
    rep(i, 0, 4) {
      current = tilt_north(current);
      current = rotate_90(current);
    }
    cycle_num++;
  }

  int cycle_start = seen[current];
  int cycle_length = cycle_num - cycle_start;
  ll remaining = (1000000000LL - cycle_start) % cycle_length;

  rep(i, 0, remaining) {
    rep(j, 0, 4) {
      current = tilt_north(current);
      current = rotate_90(current);
    }
  }

  part_two = total_load(current);

  cout << part_one << endl;
  cout << part_two << endl;
}
