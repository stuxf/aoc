#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

int main() {
  string line;
  vector<string> grid;

  int start_row = -1, start_col = -1;

  while (getline(cin, line)) {
    if (start_row == -1) {
      size_t pos = line.find('S');
      if (pos != string::npos) {
        start_row = grid.size();
        start_col = pos;
      }
    }
    grid.push_back(line);
  }

  int rows = grid.size();
  int cols = grid[0].size();

  enum Dir { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };
  int dr[] = {-1, 0, 1, 0};
  int dc[] = {0, 1, 0, -1};

  int cur_dir = -1;

  char cur;

  for (int dir = UP; dir <= LEFT; dir++) {
    int nr = start_row + dr[dir];
    int nc = start_col + dc[dir];
    cur = grid[nr][nc];

    if (dir == UP and (cur == '|' or cur == 'F' or cur == '7')) {
      cur_dir = UP;
      break;
    } else if (dir == RIGHT and (cur == '-' or cur == '7')) {
      cur_dir = RIGHT;
      break;
    } else if (dir == DOWN && (cur == '|' || cur == 'L' || cur == 'J')) {
      cur_dir = DOWN;
      break;
    } else if (dir == LEFT && (cur == '-' || cur == 'L' || cur == 'F')) {
      cur_dir = LEFT;
      break;
    }
  }

  int steps = 0;
  int r = start_row, c = start_col;
  int nr, nc;
  ll area = 0;
  while (cur != 'S') {
    nr = r + dr[cur_dir];
    nc = c + dc[cur_dir];

    area += c * nr - r * nc;

    r = nr;
    c = nc;

    cur = grid[r][c];
    if (cur == 'L') {
      cur_dir = (cur_dir == DOWN) ? RIGHT : UP;
    } else if (cur == 'J') {
      cur_dir = (cur_dir == DOWN) ? LEFT : UP;
    } else if (cur == '7') {
      cur_dir = (cur_dir == UP) ? LEFT : DOWN;
    } else if (cur == 'F') {
      cur_dir = (cur_dir == UP) ? RIGHT : DOWN;
    }
    ++steps;
  }

  area = abs(area) / 2;

  cout << steps / 2 << endl;
  cout << area - steps / 2 + 1 << endl;
}
