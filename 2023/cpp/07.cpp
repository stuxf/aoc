#include <bits/stdc++.h>
using namespace std;

struct Hand {
  string cards;
  int bid;
};

int getCardValue(char c, bool part2 = false) {
  switch (c) {
  case 'A':
    return 14;
  case 'K':
    return 13;
  case 'Q':
    return 12;
  case 'J':
    return part2 ? -1 : 11;
  case 'T':
    return 10;
  default:
    return c - '0';
  }
}

int getHandType(const string &cards, bool part2 = false) {
  map<char, int> freq;
  for (char c : cards) {
    freq[c]++;
  }

  if (part2 && freq.count('J') && freq['J'] < 5) {
    int jokers = freq['J'];
    freq.erase('J');

    int max_freq = 0;
    for (auto &p : freq) {
      max_freq = max(max_freq, p.second);
    }
    for (auto &p : freq) {
      if (p.second == max_freq) {
        p.second += jokers;
        break;
      }
    }
  }

  int freq_count[6] = {0};
  for (auto &p : freq) {
    freq_count[p.second]++;
  }

  if (freq_count[5] == 1)
    return 6;
  if (freq_count[4] == 1)
    return 5;
  if (freq_count[3] == 1 && freq_count[2] == 1)
    return 4;
  if (freq_count[3] == 1)
    return 3;
  if (freq_count[2] == 2)
    return 2;
  if (freq_count[2] == 1)
    return 1;
  return 0;
}

bool compare_hands(const Hand &a, const Hand &b, bool part2 = false) {
  int type_a = getHandType(a.cards, part2);
  int type_b = getHandType(b.cards, part2);

  if (type_a != type_b) {
    return type_a < type_b;
  }
  for (int i = 0; i < 5; i++) {
    int val_a = getCardValue(a.cards[i], part2);
    int val_b = getCardValue(b.cards[i], part2);
    if (val_a != val_b) {
      return val_a < val_b;
    }
  }
  return false;
}

bool cmp_part1(const Hand &a, const Hand &b) {
  return compare_hands(a, b, false);
}

bool cmp_part2(const Hand &a, const Hand &b) {
  return compare_hands(a, b, true);
}

int main() {
  string cards;
  int bid;
  int part_one = 0;
  int part_two = 0;
  vector<Hand> hands;
  while (cin >> cards >> bid) {
    hands.push_back({cards, bid});
  }

  sort(hands.begin(), hands.end(), cmp_part1);

  for (int i = 0; i < hands.size(); i++) {
    part_one += hands[i].bid * (i + 1);
  }
  sort(hands.begin(), hands.end(), cmp_part2);

  for (int i = 0; i < hands.size(); i++) {
    part_two += hands[i].bid * (i + 1);
  }

  cout << part_one << endl;
  cout << part_two << endl;
}
