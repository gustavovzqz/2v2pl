#ifndef SCHEDULER_INCLUDE_WAIT_GRAPH_HPP
#define SCHEDULER_INCLUDE_WAIT_GRAPH_HPP

#include <iostream>
#include <unordered_set>
#include <vector>

class WaitGraph {
 public:
  WaitGraph(int vertices);
  void add_edge(int u, int v);
  void print_WaitGraph() const;
  bool has_cycles() const;
  void remove_node(int node);
  bool is_waiting(int node);

 private:
  bool dfs(int v, std::vector<bool>& visited,
           std::vector<bool>& rec_stack) const;

  std::vector<std::unordered_set<int>> adj_;
  int vertices_;
};

#endif