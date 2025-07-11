#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll ways(ll t, ll d) {
  double discriminant = t * t - 4 * d;
  double sqrt_disc = sqrt(discriminant);

  ll low = floor((t - sqrt_disc) / 2 + 1e-9) + 1;
  ll high = ceil((t + sqrt_disc) / 2 - 1e-9) - 1;

  return max(0LL, high - low + 1);
}

int main() {
  vector<pair<ll, ll>> races;

  string time;
  string distance;
  getline(cin, time);
  getline(cin, distance);

  stringstream ts(time);
  stringstream ds(distance);

  string waste;
  ts >> waste;
  ds >> waste;

  ll part_one = 1;
  ll t_val, d_val;

  string t_big = "", d_big = "";

  while (ts >> t_val) {
    ds >> d_val;
    part_one *= ways(t_val, d_val);
    t_big += to_string(t_val);
    d_big += to_string(d_val);
  }

  ll part_two = ways(stoll(t_big), stoll(d_big));

  cout << part_one << endl;
  cout << part_two << endl;
}
