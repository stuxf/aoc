#include <bits/stdc++.h>
using namespace std;

int calibrationValue(string line) {
  int firstNum = -1, lastNum = -1;
  for (char c : line) {
    if (isdigit(c)) {
      if (firstNum == -1) {
        firstNum = c - '0';
      }
      lastNum = c - '0';
    }
  }
  return firstNum * 10 + lastNum;
}

int betterCalibrationValue(string line) {
  int firstNum = -1, lastNum = -1;
  vector<string> words = {"one", "two",   "three", "four", "five",
                          "six", "seven", "eight", "nine"};

  for (int pos = 0; pos < line.length(); pos++) {
    if (isdigit(line[pos])) {
      if (firstNum == -1) {
        firstNum = line[pos] - '0';
      }
      lastNum = line[pos] - '0';
    }

    for (int i = 0; i < words.size(); i++) {
      if (pos + words[i].length() <= line.length() &&
          line.substr(pos, words[i].length()) == words[i]) {
        if (firstNum == -1) {
          firstNum = i + 1;
        }
        lastNum = i + 1;
      }
    }
  }

  return firstNum * 10 + lastNum;
}

int main() {
  int sum = 0;
  int sumTwo = 0;
  string line;
  while (getline(cin, line)) {
    sum += calibrationValue(line);
    sumTwo += betterCalibrationValue(line);
  }
  cout << sum << endl;
  cout << sumTwo << endl;
}
