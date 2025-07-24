#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

enum ModuleType { BROADCASTER, FLIP_FLOP, CONJUNCTION };

struct Module {
  string name;
  ModuleType type;
  vector<string> destinations;
  bool state = false;
  map<string, bool> inputs;
};

struct Pulse {
  string from, to;
  bool high;
};

void send_pulse(const string &from, const string &to, bool high,
                queue<Pulse> &pulse_q, ll &low_cnt, ll &high_cnt) {
  pulse_q.push({from, to, high});
  high ? high_cnt++ : low_cnt++;
}

void process_pulses(map<string, Module> &modules, queue<Pulse> pulse_queue,
                    ll &low, ll &high, map<string, ll> &cycles,
                    const string &rx_feeder, const ll &button_press) {
  send_pulse("button", "broadcaster", false, pulse_queue, low, high);
  while (!pulse_queue.empty()) {
    Pulse p = pulse_queue.front();
    pulse_queue.pop();

    if (modules.find(p.to) == modules.end()) {
      continue;
    }

    if (p.to == rx_feeder && p.high && !cycles[p.from]) {
      cycles[p.from] = button_press;
    }
    Module &m = modules[p.to];

    switch (m.type) {
    case (BROADCASTER):
      trav(dest, m.destinations) {
        send_pulse(m.name, dest, p.high, pulse_queue, low, high);
      }
      break;
    case (FLIP_FLOP):
      if (!p.high) {
        m.state = !m.state;
        trav(dest, m.destinations) {
          send_pulse(m.name, dest, m.state, pulse_queue, low, high);
        }
      }
      break;
    case (CONJUNCTION):
      m.inputs[p.from] = p.high;
      bool all_high = true;
      trav(input, m.inputs) {
        if (!input.second) {
          all_high = false;
          break;
        }
      }

      trav(dest, m.destinations) {
        send_pulse(m.name, dest, !all_high, pulse_queue, low, high);
      }
      break;
    }
  }
}

int main() {
  string line;
  ll part_one = 0, part_two = 1;

  map<string, Module> modules;
  queue<Pulse> pulse_queue;
  ll low = 0, high = 0;

  while (getline(cin, line)) {
    size_t arrow_pos = line.find(" -> ");
    if (arrow_pos == string::npos) {
      continue;
    }

    string module_part = line.substr(0, arrow_pos);
    string dest_part = line.substr(arrow_pos + 4);

    Module m;

    if (module_part == "broadcaster") {
      m.name = "broadcaster";
      m.type = BROADCASTER;
    } else if (module_part[0] == '%') {
      m.name = module_part.substr(1);
      m.type = FLIP_FLOP;
    } else if (module_part[0] == '&') {
      m.name = module_part.substr(1);
      m.type = CONJUNCTION;
    } else {
      continue;
    }

    stringstream ss(dest_part);
    string dest;

    while (getline(ss, dest, ',')) {
      if (dest[0] == ' ') {
        dest = dest.substr(1);
      }
      m.destinations.push_back(dest);
    }

    modules[m.name] = m;
  }

  trav(module, modules) {
    if (module.second.type == CONJUNCTION) {
      trav(other_module, modules) {
        trav(destination, other_module.second.destinations) {
          if (destination == module.first) {
            modules[module.first].inputs[other_module.first] = false;
          }
        }
      }
    }
  }

  string rx_feeder = "";
  trav(mod, modules) {
    trav(dest, mod.second.destinations) {
      if (dest == "rx") {
        rx_feeder = mod.first;
        break;
      }
    }
    if (!rx_feeder.empty())
      break;
  }

  map<string, ll> cycles;
  if (!rx_feeder.empty() && modules[rx_feeder].type == CONJUNCTION) {
    trav(input, modules[rx_feeder].inputs) { cycles[input.first] = 0; }
  }

  ll button_press = 0;

  while (true) {
    process_pulses(modules, pulse_queue, low, high, cycles, rx_feeder,
                   ++button_press);

    if (button_press == 1000) {
      part_one = low * high;
    }

    bool all_found = true;

    trav(cycle, cycles) {
      if (!cycle.second) {
        all_found = false;
        break;
      }
    }

    if (all_found) {
      break;
    }
  }

  trav(cycle, cycles) { part_two = lcm(part_two, cycle.second); }
  cout << part_one << endl;
  cout << part_two << endl;
}
