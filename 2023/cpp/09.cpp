#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

ll extrapolate(vector<ll> &v) {
  if (all_of(v.begin(), v.end(), [](ll x) { return x == 0; })) {
    return 0;
  }

  vector<ll> diff;
  for (int i = 1; i < v.size(); i++) {
    diff.push_back(v[i] - v[i - 1]);
  }

  return v.back() + extrapolate(diff);
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;
  while (getline(cin, line)) {
    vector<ll> nums;
    istringstream iss(line);
    ll num;
    while (iss >> num) {
      nums.push_back(num);
    }
    part_one += extrapolate(nums);
    reverse(nums.begin(), nums.end());
    part_two += extrapolate(nums);
  }
  cout << part_one << endl;
  cout << part_two << endl;
}
