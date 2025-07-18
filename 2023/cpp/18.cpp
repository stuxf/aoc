#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  int cur_r1 = 0, cur_c1 = 0;
  int circumference1 = 0;
  int area1 = 0;

  int cur_r2 = 0, cur_c2 = 0;
  ll circumference2 = 0;
  ll area2 = 0;
  while (getline(cin, line)) {
    stringstream ss(line);

    char direction1;
    int distance1;
    string color;

    ss >> direction1 >> distance1 >> color;

    color = color.substr(2, color.length() - 3);
    circumference1 += distance1;

    int prev_c1 = cur_c1;
    int prev_r1 = cur_r1;

    switch (direction1) {
    case 'R':
      cur_c1 += distance1;
      break;
    case 'D':
      cur_r1 += distance1;
      break;
    case 'L':
      cur_c1 -= distance1;
      break;
    case 'U':
      cur_r1 -= distance1;
      break;
    }

    char direction2 = color.back();
    color = color.substr(0, color.length() - 1);

    ll distance2 = stoll(color, nullptr, 16);;
    circumference2 += distance2;

    ll prev_c2 = cur_c2;
    ll prev_r2 = cur_r2;

    switch (direction2) {
    case '0':
      cur_c2 += distance2;
      break;
    case '1':
      cur_r2 += distance2;
      break;
    case '2':
      cur_c2 -= distance2;
      break;
    case '3':
      cur_r2 -= distance2;
      break;
    }

    area1 += prev_c1 * cur_r1 - cur_c1 * prev_r1;
    area2 += prev_c2 * cur_r2 - cur_c2 * prev_r2;
  }

  part_one = abs(area1) / 2 + circumference1 / 2 + 1;
  part_two = abs(area2) / 2 + circumference2 / 2 + 1;

  cout << part_one << endl;
  cout << part_two << endl;
}
