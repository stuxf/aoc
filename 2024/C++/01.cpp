#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second

const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LLINF = 1e18;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

void solve() {
  freopen("../inputs/01.txt", "r", stdin);

  vi left, right;
  int x, y;
  while (cin >> x >> y) {
    left.pb(x);
    right.pb(y);
  }

  sort(all(left));
  sort(all(right));

  ll ans1 = 0;

  rep(i, 0, sz(left)) { ans1 += abs(left[i] - right[i]); }

  cout << ans1 << endl;

  unordered_map<int, int> freq;
  trav(x, right) freq[x]++;

  ll ans2 = 0;
  trav(x, left) ans2 += x * freq[x];
  cout << ans2 << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}