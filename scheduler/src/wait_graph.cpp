#include "scheduler/include/wait_graph.hpp"

WaitGraph::WaitGraph(int vertices) : vertices_(vertices) {
  adj_.resize(vertices_);
}

void WaitGraph::add_edge(int u, int v) { adj_[u].insert(v); }

void WaitGraph::print_WaitGraph() const {
  for (int i = 0; i < vertices_; ++i) {
    std::cout << "Vertex " << i << ": ";
    for (int neighbor : adj_[i]) {
      std::cout << neighbor << " ";
    }
    std::cout << std::endl;
  }
}

void WaitGraph::remove_node(int node) {
  adj_[node].clear();

  for (int i = 0; i < vertices_; ++i) {
    adj_[i].erase(node);
  }
}

bool WaitGraph::is_waiting(int node) { return (!(adj_[node].empty())); }

bool WaitGraph::has_cycles() const {
  std::vector<bool> visited(vertices_, false);
  std::vector<bool> rec_stack(vertices_, false);

  for (int i = 0; i < vertices_; ++i) {
    if (!visited[i] && dfs(i, visited, rec_stack)) {
      return true;
    }
  }
  return false;
}

bool WaitGraph::dfs(int v, std::vector<bool>& visited,
                    std::vector<bool>& rec_stack) const {
  visited[v] = true;
  rec_stack[v] = true;

  for (int neighbor : adj_[v]) {
    if (!visited[neighbor] && dfs(neighbor, visited, rec_stack)) {
      return true;
    } else if (rec_stack[neighbor]) {
      return true;
    }
  }

  rec_stack[v] = false;
  return false;
}
