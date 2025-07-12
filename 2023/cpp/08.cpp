#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

pair<int, ll> find_steps(map<string, pair<string, string>> &net,
                         string &instr) {
  pair<int, ll> steps;
  string node = "AAA";
  int instr_size = sz(instr);
  int instr_idx = 0;
  while (node != "ZZZ") {
    instr_idx %= instr_size;
    if (instr[instr_idx++] == 'L') {
      node = net[node].first;
    } else {
      node = net[node].second;
    }
    steps.first++;
  }

  vector<string> nodes;
  trav(item, net) {
    if (item.first[2] == 'A') {
      nodes.push_back(item.first);
    }
  }
  instr_idx = 0;

  vector<ll> cycle_lengths;
  trav(start_node, nodes) {
    string current = start_node;
    ll cycle_steps = 0;
    instr_idx = 0;

    while (current[2] != 'Z') {
      if (instr[instr_idx] == 'L') {
        current = net[current].first;
      } else {
        current = net[current].second;
      }
      cycle_steps++;
      instr_idx = (instr_idx + 1) % instr_size;
    }
    cycle_lengths.push_back(cycle_steps);
  }

  steps.second = cycle_lengths[0];
  rep(i, 1, sz(cycle_lengths)) {
    steps.second = lcm(steps.second, cycle_lengths[i]);
  }

  return steps;
}

int main() {
  string instructions;
  cin >> instructions;
  cout << instructions << endl;

  map<string, pair<string, string>> graph;

  string line;
  while (getline(cin, line)) {
    if (line.empty()) {
      continue;
    }

    string node = line.substr(0, 3);
    string left = line.substr(7, 3);
    string right = line.substr(12, 3);

    graph[node] = {left, right};
  }
  pair<int, ll> ans = find_steps(graph, instructions);
  int part_one = ans.first;
  ll part_two = ans.second;

  cout << part_one << endl;
  cout << part_two << endl;
}
