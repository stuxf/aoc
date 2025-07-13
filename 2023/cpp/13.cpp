#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

pair<ll, ll> process(const vector<uint32_t> &pattern, int multiplier) {
  ll perfect = 0, smudged = 0;
  rep(mirror, 0, sz(pattern) - 1) {
    int smudges = 0;
    for (int left = mirror, right = mirror + 1;
         left >= 0 && right < sz(pattern); --left, ++right) {
      smudges += __builtin_popcount(pattern[left] ^ pattern[right]);
    }
    if (smudges == 0)
      perfect += (mirror + 1) * multiplier;
    if (smudges == 1)
      smudged += (mirror + 1) * multiplier;
  }
  return {perfect, smudged};
}

int main() {
  string line;
  vector<uint32_t> rows, cols;
  ll part_one = 0, part_two = 0;

  while (getline(cin, line)) {
    if (line == "") {
      auto [horiz_perfect, horiz_smudged] = process(rows, 100);
      auto [vert_perfect, vert_smudged] = process(cols, 1);
      part_one += horiz_perfect + vert_perfect;
      part_two += horiz_smudged + vert_smudged;

      rows.clear();
      cols.clear();
    } else {
      if (sz(cols) == 0) {
        cols.resize(sz(line));
      }
      uint32_t row_pattern = 0;
      int row_idx = sz(rows);
      rep(i, 0, sz(line)) {
        uint32_t is_rock = (line[i] == '#');
        row_pattern |= is_rock << i;
        cols[i] |= is_rock << row_idx;
      }
      rows.push_back(row_pattern);
    }
  }
  auto [horiz_perfect, horiz_smudged] = process(rows, 100);
  auto [vert_perfect, vert_smudged] = process(cols, 1);
  part_one += horiz_perfect + vert_perfect;
  part_two += horiz_smudged + vert_smudged;

  cout << part_one << endl;
  cout << part_two << endl;
}
