#include <bits/stdc++.h>
#include <random>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto &a : x)

mt19937 rng(0);

struct Edge {
  int u, v;
};

struct DSU {
  vector<int> parent;
  DSU(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int i) {
    if (parent[i] == i)
      return i;
    return parent[i] = find(parent[i]);
  }

  void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
      parent[root_i] = root_j;
    }
  }
};

int main() {
  string line;
  ll part_one = 0;

  map<string, vector<string>> graph;

  map<string, vector<string>> adj;
  set<string> node_names;

  while (getline(cin, line)) {
    stringstream ss(line);
    string source;
    getline(ss, source, ':');

    string component;
    while (ss >> component) {
      adj[source].push_back(component);
      adj[component].push_back(source);
      node_names.insert(source);
      node_names.insert(component);
    }
  }

  map<string, int> name_to_id;
  int next_id = 0;
  for (const auto &name : node_names) {
    name_to_id[name] = next_id++;
  }

  vector<Edge> all_edges;
  for (const auto &pair : adj) {
    string u_name = pair.first;
    int u_id = name_to_id[u_name];
    for (const auto &v_name : pair.second) {
      int v_id = name_to_id[v_name];
      if (u_id < v_id) {
        all_edges.push_back({u_id, v_id});
      }
    }
  }

  int n = node_names.size();

  while (true) {
    DSU dsu(n);
    int num_vertices = n;

    shuffle(all_edges.begin(), all_edges.end(), rng);

    for (const auto &edge : all_edges) {
      if (num_vertices <= 2)
        break;
      if (dsu.find(edge.u) != dsu.find(edge.v)) {
        dsu.unite(edge.u, edge.v);
        num_vertices--;
      }
    }

    int current_cut_size = 0;
    for (const auto &edge : all_edges) {
      if (dsu.find(edge.u) != dsu.find(edge.v)) {
        current_cut_size++;
      }
    }

    if (current_cut_size == 3) {
      map<int, int> partition_sizes;
      for (int i = 0; i < n; ++i) {
        partition_sizes[dsu.find(i)]++;
      }

      ll result = 1;
      for (auto const &[root, size] : partition_sizes) {
        result *= size;
      }
      part_one = result;
      break;
    }
  }

  cout << part_one << endl;
}
