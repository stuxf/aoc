#include <bits/stdc++.h>
using namespace std;

pair<int, int> gamePossible(string line) {
  vector<int> limits = {12, 13, 14};
  int i = 5;
  int gameId = 0;

  while (isdigit(line[i])) {
    gameId = gameId * 10 + (line[i] - '0');
    ++i;
  }
  ++i;

  int curNum = 0;
  vector<int> rgbReal = {0, 0, 0};
  vector<int> rgbMax = {0, 0, 0};
  bool possible = true;

  for (; i < line.length(); ++i) {
    if (isdigit(line[i])) {
      curNum = curNum * 10 + (line[i] - '0');
    } else {
      switch (line[i]) {
      case 'r':
        rgbReal[0] += curNum;
        curNum = 0;
        break;
      case 'g':
        rgbReal[1] += curNum;
        curNum = 0;
        break;
      case 'b':
        rgbReal[2] += curNum;
        curNum = 0;
        break;
      case ';':
        for (int j = 0; j < 3; j++) {
          if (rgbReal[j] > limits[j]) {
            possible = false;
          }
          rgbMax[j] = max(rgbMax[j], rgbReal[j]);
        }
        rgbReal = {0, 0, 0};
        break;
      }
    }
  }

  for (int j = 0; j < 3; j++) {
    if (rgbReal[j] > limits[j]) {
      possible = false;
    }
    rgbMax[j] = max(rgbMax[j], rgbReal[j]);
  }

  int part1Result = possible ? gameId : 0;
  int part2Power = rgbMax[0] * rgbMax[1] * rgbMax[2];

  return {part1Result, part2Power};
}

int main() {
  string line;
  int sum = 0;
  int power = 0;
  pair<int, int> gameIdPower;
  while (getline(cin, line)) {
    gameIdPower = gamePossible(line);
    sum += gameIdPower.first;
    power += gameIdPower.second;
  }
  cout << sum << endl;
  cout << power << endl;
}
