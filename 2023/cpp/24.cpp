#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

struct Hailstone {
  ll px, py, pz;
  ll vx, vy, vz;
};

const ll MIN_COLLIDE = 200000000000000LL;
const ll MAX_COLLIDE = 400000000000000LL;

vector<long double> solve_linear_system(vector<vector<long double>> A,
                                        vector<long double> b) {
  int n = A.size();

  for (int i = 0; i < n; i++) {
    int max_row = i;
    for (int k = i + 1; k < n; k++) {
      if (abs(A[k][i]) > abs(A[max_row][i])) {
        max_row = k;
      }
    }
    swap(A[i], A[max_row]);
    swap(b[i], b[max_row]);

    for (int k = i + 1; k < n; k++) {
      long double factor = A[k][i] / A[i][i];
      for (int j = i; j < n; j++) {
        A[k][j] -= factor * A[i][j];
      }
      b[k] -= factor * b[i];
    }
  }

  vector<long double> x(n);
  for (int i = n - 1; i >= 0; i--) {
    long double sum = 0;
    for (int j = i + 1; j < n; j++) {
      sum += A[i][j] * x[j];
    }
    x[i] = (b[i] - sum) / A[i][i];
  }

  return x;
}

bool intersects(const Hailstone &h1, const Hailstone &h2) {
  __int128_t px1 = h1.px, py1 = h1.py, vx1 = h1.vx, vy1 = h1.vy;
  __int128_t px2 = h2.px, py2 = h2.py, vx2 = h2.vx, vy2 = h2.vy;

  __int128_t D = vx1 * vy2 - vx2 * vy1;

  if (D == 0) {
    return false;
  }

  long double x_intersect = (long double)((px1 * vy1 - py1 * vx1) * vx2 -
                                          (px2 * vy2 - py2 * vx2) * vx1) /
                            -D;
  long double y_intersect = (long double)((px1 * vy1 - py1 * vx1) * vy2 -
                                          (px2 * vy2 - py2 * vx2) * vy1) /
                            -D;

  if ((x_intersect - px1) / vx1 < 0 || (x_intersect - px2) / vx2 < 0) {
    return false;
  }

  if (x_intersect < MIN_COLLIDE || x_intersect > MAX_COLLIDE ||
      y_intersect < MIN_COLLIDE || y_intersect > MAX_COLLIDE) {
    return false;
  }

  return true;
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  vector<Hailstone> hailstones;
  while (getline(cin, line)) {
    trav(c, line) {
      if (c == '@' or c == ',') {
        c = ' ';
      }
    }

    stringstream ss(line);

    ll px, py, pz, vx, vy, vz;
    if (ss >> px >> py >> pz >> vx >> vy >> vz) {
      hailstones.push_back({px, py, pz, vx, vy, vz});
    }
  }

  rep(i, 0, sz(hailstones)) {
    rep(j, i + 1, sz(hailstones)) {
      if (intersects(hailstones[i], hailstones[j])) {
        ++part_one;
      }
    }
  }

  Hailstone h1 = hailstones[0];
  Hailstone h2 = hailstones[1];
  Hailstone h3 = hailstones[2];

  vector<vector<__int128_t>> A_128(6, vector<__int128_t>(6));
  vector<__int128_t> b_128(6);

  A_128[0][1] = h1.vz - h2.vz;
  A_128[0][2] = h2.vy - h1.vy;
  A_128[0][4] = h2.pz - h1.pz;
  A_128[0][5] = h1.py - h2.py;
  b_128[0] = h1.py * h1.vz - h1.pz * h1.vy - (h2.py * h2.vz - h2.pz * h2.vy);

  A_128[1][0] = h2.vz - h1.vz;
  A_128[1][2] = h1.vx - h2.vx;
  A_128[1][3] = h1.pz - h2.pz;
  A_128[1][5] = h2.px - h1.px;
  b_128[1] = h1.pz * h1.vx - h1.px * h1.vz - (h2.pz * h2.vx - h2.px * h2.vz);

  A_128[2][0] = h1.vy - h2.vy;
  A_128[2][1] = h2.vx - h1.vx;
  A_128[2][3] = h2.py - h1.py;
  A_128[2][4] = h1.px - h2.px;
  b_128[2] = h1.px * h1.vy - h1.py * h1.vx - (h2.px * h2.vy - h2.py * h2.vx);

  A_128[3][1] = h1.vz - h3.vz;
  A_128[3][2] = h3.vy - h1.vy;
  A_128[3][4] = h3.pz - h1.pz;
  A_128[3][5] = h1.py - h3.py;
  b_128[3] = h1.py * h1.vz - h1.pz * h1.vy - (h3.py * h3.vz - h3.pz * h3.vy);

  A_128[4][0] = h3.vz - h1.vz;
  A_128[4][2] = h1.vx - h3.vx;
  A_128[4][3] = h1.pz - h3.pz;
  A_128[4][5] = h3.px - h1.px;
  b_128[4] = h1.pz * h1.vx - h1.px * h1.vz - (h3.pz * h3.vx - h3.px * h3.vz);

  A_128[5][0] = h1.vy - h3.vy;
  A_128[5][1] = h3.vx - h1.vx;
  A_128[5][3] = h3.py - h1.py;
  A_128[5][4] = h1.px - h3.px;
  b_128[5] = h1.px * h1.vy - h1.py * h1.vx - (h3.px * h3.vy - h3.py * h3.vx);

  vector<vector<long double>> A_ld(6, vector<long double>(6));
  vector<long double> b_ld(6);
  for (int i = 0; i < 6; ++i) {
    b_ld[i] = (long double)b_128[i];
    for (int j = 0; j < 6; ++j) {
      A_ld[i][j] = (long double)A_128[i][j];
    }
  }

  vector<long double> solution = solve_linear_system(A_ld, b_ld);

  ll Px = round(solution[0]);
  ll Py = round(solution[1]);
  ll Pz = round(solution[2]);
  part_two = Px + Py + Pz;

  cout << part_one << endl;
  cout << part_two << endl;
}
