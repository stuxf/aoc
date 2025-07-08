#include <bits/stdc++.h>
using namespace std;
bool isSymbol(char c) { return c != '.' && !isdigit(c); }
int main() {
  vector<string> engineGrid;
  string line;
  while (getline(cin, line)) {
    engineGrid.push_back(line);
  }
  int sum = 0;
  map<pair<int, int>, vector<int>> gears;

  for (int row = 0; row < engineGrid.size(); row++) {
    int curNum = 0;
    bool nextToSymbol = false;
    set<pair<int, int>> gearLocations;

    for (int col = 0; col < engineGrid[row].size(); col++) {
      if (isdigit(engineGrid[row][col])) {
        curNum = curNum * 10 + engineGrid[row][col] - '0';

        if (row > 0) {
          if (isSymbol(engineGrid[row - 1][col])) {
            nextToSymbol = true;
            if (engineGrid[row - 1][col] == '*') {
              gearLocations.insert({row - 1, col});
            }
          } else if (col > 0 && isSymbol(engineGrid[row - 1][col - 1])) {
            if (engineGrid[row - 1][col - 1] == '*') {
              gearLocations.insert({row - 1, col - 1});
            }
            nextToSymbol = true;
          } else if (col < (engineGrid[row].size() - 1) &&
                     isSymbol(engineGrid[row - 1][col + 1])) {
            if (engineGrid[row - 1][col + 1] == '*') {
              gearLocations.insert({row - 1, col + 1});
            }
            nextToSymbol = true;
          }
        }
        if (row < (engineGrid.size() - 1)) {
          if (isSymbol(engineGrid[row + 1][col])) {
            if (engineGrid[row + 1][col] == '*') {
              gearLocations.insert({row + 1, col});
            }
            nextToSymbol = true;
          } else if (col > 0 && isSymbol(engineGrid[row + 1][col - 1])) {
            if (engineGrid[row + 1][col - 1] == '*') {
              gearLocations.insert({row + 1, col - 1});
            }
            nextToSymbol = true;
          } else if (col < (engineGrid[row].size() - 1) &&
                     isSymbol(engineGrid[row + 1][col + 1])) {
            if (engineGrid[row + 1][col + 1] == '*') {
              gearLocations.insert({row + 1, col + 1});
            }
            nextToSymbol = true;
          }
        }
        if (col > 0 && isSymbol(engineGrid[row][col - 1])) {
          nextToSymbol = true;
          if (engineGrid[row][col - 1] == '*') {
            gearLocations.insert({row, col - 1});
          }
        }
        if (col < (engineGrid[row].size() - 1) &&
            isSymbol(engineGrid[row][col + 1])) {
          if (engineGrid[row][col + 1] == '*') {
            gearLocations.insert({row, col + 1});
          }
          nextToSymbol = true;
        }
      } else {
        if (curNum != 0 && nextToSymbol) {
          sum += curNum;
        }
        if (curNum != 0 && !gearLocations.empty()) {
          for (pair<int, int> location : gearLocations) {
            gears[location].push_back(curNum);
          }
        }
        curNum = 0;
        nextToSymbol = false;
        gearLocations.clear();
      }
    }
    if (curNum != 0 && nextToSymbol) {
      sum += curNum;
    }
    if (curNum != 0 && !gearLocations.empty()) {
      for (pair<int, int> location : gearLocations) {
        gears[location].push_back(curNum);
      }
    }
  }

  int gearSum = 0;
  for (const auto &[pos, nums] : gears) {
    if (nums.size() == 2) {
      gearSum += nums[0] * nums[1];
    }
  }

  cout << sum << endl;
  cout << gearSum << endl;
}
