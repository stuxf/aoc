#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

ll interpolate(vector<pair<ll, ll>> &datapoints, ll xi) {
  ll result = 0;
  int n = sz(datapoints);
  rep(i, 0, n) {
    ll term = datapoints[i].second;
    rep(j, 0, n) {
      if (i != j) {
        term *= (xi - datapoints[j].first) /
                (datapoints[i].first - datapoints[j].first);
      }
    }
    result += term;
  }
  return result;
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  vector<string> grid;

  int start_r = -1, start_c = -1;

  while (getline(cin, line)) {
    grid.push_back(line);
    if (start_c != -1) {
      continue;
    }
    ++start_r;
    rep(i, 0, sz(line)) {
      if (line[i] == 'S') {
        start_c = i;
        break;
      }
    }
  }
  int rows = sz(grid), cols = sz(grid[0]);

  set<pair<ll, ll>> cur = {{start_r, start_c}};

  int dc[] = {0, 1, 0, -1};
  int dr[] = {-1, 0, 1, 0};

  vector<pair<ll, ll>> datapoints;

  rep(i, 0, 65 + rows * 2) {
    set<pair<ll, ll>> next;
    trav(loc, cur) {
      rep(d, 0, 4) {
        ll new_r = loc.first + dr[d];
        ll new_c = loc.second + dc[d];

        ll grid_r = new_r % rows;
        ll grid_c = new_c % cols;

        if (grid_r < 0) {
          grid_r += rows;
        }

        if (grid_c < 0) {
          grid_c += cols;
        }

        if (grid[grid_r][grid_c] == '#') {
          continue;
        }

        next.insert({new_r, new_c});
      }
    }
    cur = next;
    if (i == 63) {
      part_one = cur.size();
    }
    if (((i + 1) % rows) == 65) {
      datapoints.push_back({i + 1, cur.size()});
    }
  }

  part_two = interpolate(datapoints, 26501365);

  cout << part_one << endl;
  cout << part_two << endl;
}
