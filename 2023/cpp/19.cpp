#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

ll combos(const string &workflow_name,
          const unordered_map<string, vector<pair<string, string>>> &workflows,
          unordered_map<char, pair<int, int>> current_ranges) {
  if (workflow_name == "R") {
    return 0;
  }
  if (workflow_name == "A") {
    long long combinations = 1;
    for (auto const &[category, range] : current_ranges) {
      combinations *= (range.second - range.first + 1);
    }
    return combinations;
  }

  ll total_accepted = 0;

  const auto &workflow = workflows.at(workflow_name);

  trav(rule, workflow) {
    const string &condition = rule.first;
    const string &destination = rule.second;

    if (condition.empty()) {
      total_accepted += combos(destination, workflows, current_ranges);
      continue;
    }

    char category = condition[0];
    char op = condition[1];
    int value = stoi(condition.substr(2));

    auto true_ranges = current_ranges;

    if (op == '<') {
      true_ranges[category].second =
          min(true_ranges[category].second, value - 1);
      current_ranges[category].first =
          max(current_ranges[category].first, value);

    } else {
      true_ranges[category].first = max(true_ranges[category].first, value + 1);
      current_ranges[category].second =
          min(current_ranges[category].second, value);
    }

    if (true_ranges[category].first <= true_ranges[category].second) {
      total_accepted += combos(destination, workflows, true_ranges);
    }

    if (current_ranges[category].first > current_ranges[category].second) {
      break;
    }
  }
  return total_accepted;
}

int main() {
  string line;
  ll part_one = 0, part_two = 0;

  unordered_map<string, vector<pair<string, string>>> workflows;

  while (getline(cin, line) && !line.empty()) {
    int brace_pos = line.find('{');
    string name = line.substr(0, brace_pos);

    string rules_str =
        line.substr(brace_pos + 1, line.length() - brace_pos - 2);

    stringstream ss(rules_str);
    string rule_token;

    vector<pair<string, string>> parsed_rules;

    while (getline(ss, rule_token, ',')) {
      size_t colon_pos = rule_token.find(':');

      if (colon_pos != string::npos) {
        string condition = rule_token.substr(0, colon_pos);
        string destination = rule_token.substr(colon_pos + 1);
        parsed_rules.push_back({condition, destination});
      } else {
        parsed_rules.push_back({"", rule_token});
      }
    }
    workflows[name] = parsed_rules;
  }

  while (getline(cin, line)) {
    unordered_map<char, int> current_part;
    line = line.substr(1, line.length() - 2);

    stringstream ss(line);
    string rating_token;

    while (getline(ss, rating_token, ',')) {
      char category = rating_token[0];
      int value = stoi(rating_token.substr(2));
      current_part[category] = value;
    }

    string current_workflow_name = "in";

    while (current_workflow_name != "A" && current_workflow_name != "R") {
      const auto &current_rules = workflows[current_workflow_name];

      trav(rule, current_rules) {
        const string &condition = rule.first;
        const string &destination = rule.second;

        if (condition.empty()) {
          current_workflow_name = destination;
          break;
        }

        char category = condition[0];
        char op = condition[1];
        int value = stoi(condition.substr(2));

        int part_value = current_part[category];
        bool condition_met = false;

        if (op == '<') {
          condition_met = (part_value < value);
        } else {
          condition_met = (part_value > value);
        }

        if (condition_met) {
          current_workflow_name = destination;
          break;
        }
      }

      if (current_workflow_name == "A") {
        part_one += current_part['x'];
        part_one += current_part['m'];
        part_one += current_part['a'];
        part_one += current_part['s'];
      }
    }
  }

  unordered_map<char, pair<int, int>> rating_ranges;
  rating_ranges['x'] = {1, 4000};
  rating_ranges['m'] = {1, 4000};
  rating_ranges['a'] = {1, 4000};
  rating_ranges['s'] = {1, 4000};

  part_two = combos("in", workflows, rating_ranges);

  cout << part_one << endl;
  cout << part_two << endl;
}
