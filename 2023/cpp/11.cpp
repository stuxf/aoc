#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

ll distance(pair<ll, ll> a, pair<ll,ll> b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
  vector<pair<ll, ll>> galaxies;
  string line;
  vector<string> grid;
  ll row = 0;
  set<ll> gals_with_cols;

  while (getline(cin, line)) {
    ll col = line.find('#');
    if (col == string::npos) {
      row += 1'000'000 - 1;
    }
    while (col != string::npos) {
      gals_with_cols.insert(col);
      galaxies.push_back({row, col});
      col = line.find('#', col + 1);
    }
    row++;
    grid.push_back(line);
  }

  ll offset = 0;
  rep(col, 0, grid[0].size()) {
    if (!gals_with_cols.count(col)) {
      trav(gal, galaxies) {
        if (gal.second > col + offset) {
          gal.second += 1'000'000 - 1;
        }
      }
      offset += 1'000'000 - 1;
    }
  }

  ll part_one = 0;
  rep(gal1, 0, galaxies.size()) {
    rep(gal2, gal1 + 1, galaxies.size()) {
      part_one += distance(galaxies[gal1], galaxies[gal2]); 
    }
  }

  cout << part_one << endl;
}
