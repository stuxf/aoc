#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

pair<int, int> solve(const string &str) {
  int sum = 0;
  int box;
  trav(c, str) {
    if (c == '-' or c == '=') {
      box = sum;
    }
    sum += c;
    sum *= 17;
    sum %= 256;
  }
  return {sum, box};
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  getline(cin, line);

  istringstream iss(line);
  string s;

  vector<pair<string, int>> hashmap[256];

  while (getline(iss, s, ',')) {
    pair<int, int> nums = solve(s);
    part_one += nums.first;
    if (s.back() == '-') {
      string removal = s.substr(0, s.length() - 1);
      rep(box_idx, 0, hashmap[nums.second].size()) {
        if (hashmap[nums.second][box_idx].first == removal) {
          hashmap[nums.second].erase(hashmap[nums.second].begin() + box_idx);
          break;
        }
      }
    } else {
      string to_add = s.substr(0, s.length() - 2);
      bool found = false;
      rep(box_idx, 0, hashmap[nums.second].size()) {
        if (hashmap[nums.second][box_idx].first == to_add) {
          found = true;
          hashmap[nums.second][box_idx].second = s.back() - '0';
          break;
        }
      }

      if (!found) {
        hashmap[nums.second].push_back({to_add , s.back() - '0'});
      }
    }
  }

  for (int box_num = 0; box_num < 256; box_num++) {
    for (int slot = 0; slot < hashmap[box_num].size(); slot++) {
      part_two += (box_num + 1) * (slot + 1) * hashmap[box_num][slot].second;
    }
  }

  cout << part_one << endl;
  cout << part_two << endl;
}
