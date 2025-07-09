#include <bits/stdc++.h>
using namespace std;

int numMatches(const string &card) {
  istringstream ss(card);
  unordered_set<int> winners;
  ss.ignore(INT_MAX, ':');

  string token;
  while (ss >> token && token != "|") {
    winners.insert(stoi(token));
  }

  int num, matches = 0;
  while (ss >> num) {
    matches += winners.count(num);
  }

  return matches;
}

int main() {
  string line;
  vector<int> matches;
  while (getline(cin, line)) {
    matches.push_back(numMatches(line));
  }

  int points = 0;
  for (int m : matches) {
    if (m > 0)
      points += (1 << (m - 1));
  }

  int n = matches.size();
  vector<int> cards(n, 1);

  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= matches[i] && i + j < n; j++) {
      cards[i + j] += cards[i];
    }
  }

  cout << points << endl;
  cout << accumulate(cards.begin(), cards.end(), 0) << endl;
}
