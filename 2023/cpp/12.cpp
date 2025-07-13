#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

ll possible_combos(const string &springs, const vector<int> &groups, int pos,
                   int group, int run, map<tuple<int, int, int>, ll> &memo) {
  auto key = make_tuple(pos, group, run);
  if (memo.count(key)) {
    return memo[key];
  }

  if (pos == springs.size()) {
    if (run > 0) {
      return (group + 1 == groups.size() && run == groups[group]) ? 1 : 0;
    }
    return (group == groups.size()) ? 1 : 0;
  }

  ll result = 0;
  char c = springs[pos];

  if (c == '.' || c == '?') {
    if (run > 0) {
      if (group < groups.size() && run == groups[group])
        result += possible_combos(springs, groups, pos + 1, group + 1, 0, memo);
    } else {
      result += possible_combos(springs, groups, pos + 1, group, 0, memo);
    }
  }

  if (c == '#' || c == '?') {
    result += possible_combos(springs, groups, pos + 1, group, run + 1, memo);
  }

  return memo[key] = result;
};

int main() {
  string line;
  string spring;

  ll part_one = 0, part_two = 0;

  while (getline(cin, line)) {
    int pos = line.find(' ');
    string springs = line.substr(0, pos);

    vector<int> groups;
    stringstream ss(line.substr(pos + 1));

    for (int x; ss >> x; groups.push_back(x)) {
      if (ss.peek() == ',') {
        ss.ignore();
      }
    }
    map<tuple<int, int, int>, ll> memo;

    part_one += possible_combos(springs, groups, 0, 0, 0, memo);

    string unfolded_springs = springs;
    vector<int> unfolded_groups = groups;

    rep(i, 0, 4) {
      unfolded_springs += "?" + springs;
      unfolded_groups.insert(unfolded_groups.end(), groups.begin(),
                             groups.end());
    }

    map<tuple<int, int, int>, ll> memo2;
    part_two +=
        possible_combos(unfolded_springs, unfolded_groups, 0, 0, 0, memo2);
  }

  cout << part_one << endl;
  cout << part_two << endl;
}
