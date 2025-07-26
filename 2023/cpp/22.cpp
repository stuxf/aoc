#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

struct Brick {
  int x1, y1, z1, x2, y2, z2;

  Brick(int x1, int y1, int z1, int x2, int y2, int z2)
      : x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2) {}
};

Brick dropped_brick(map<pair<int, int>, int> &tallest, const Brick &brick) {
  int peak = 0;
  rep(x, brick.x1, brick.x2 + 1) {
    rep(y, brick.y1, brick.y2 + 1) { peak = max(peak, tallest[{x, y}]); }
  }

  int dz = max(brick.z1 - peak - 1, 0);

  return Brick(brick.x1, brick.y1, brick.z1 - dz, brick.x2, brick.y2,
               brick.z2 - dz);
}

pair<int, vector<Brick>> drop(const vector<Brick> &tower) {
  map<pair<int, int>, int> tallest;
  vector<Brick> new_tower;
  int falls = 0;
  trav(brick, tower) {
    Brick new_brick = dropped_brick(tallest, brick);
    if (new_brick.z1 != brick.z1) {
      ++falls;
    }

    new_tower.push_back(new_brick);
    rep(x, new_brick.x1, new_brick.x2 + 1) {
      rep(y, new_brick.y1, new_brick.y2 + 1) { tallest[{x, y}] = new_brick.z2; }
    }
  }

  return {falls, new_tower};
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  vector<Brick> bricks;
  while (getline(cin, line)) {
    vector<int> coords;

    stringstream ss(line);
    string token;

    while (getline(ss, token, '~')) {
      stringstream token_ss(token);
      string coord;
      while (getline(token_ss, coord, ',')) {
        coords.push_back(stoi(coord));
      }
    }

    bricks.emplace_back(coords[0], coords[1], coords[2], coords[3], coords[4],
                        coords[5]);
  }

  sort(bricks.begin(), bricks.end(),
       [](const Brick &a, const Brick &b) { return a.z1 < b.z1; });

  bricks = drop(bricks).second;

  rep(i, 0, sz(bricks)) {
    vector<Brick> removed;
    rep(j, 0, sz(bricks)) {
      if (i == j)
        continue;
      removed.push_back(bricks[j]);
    }

    int falls = drop(removed).first;

    if (falls == 0) {
      ++part_one;
    } else {
      part_two += falls;
    }
  }

  cout << part_one << endl;
  cout << part_two << endl;
}
