#include "s21_graph_algorithms.h"

#include <queue>

bool IsNotVisited(const std::vector<int> &v, int vertex) {
  bool res{true};

  for (size_t i = 0; i < v.size(); i++) {
    if (v[i] == vertex) res = false;
  }

  return res;
}

void InitializationVisitVector(std::vector<std::vector<bool>> &v,
                               const S21Matrix &graph_matrix) {
  for (int i = 0; i < graph_matrix.GetRows(); i++)
    for (int j = 0; j < graph_matrix.GetRows(); j++)
      if (graph_matrix(i, j)) v[i][j] = true;
}

void InitializationVertexStack(s21::Stack<std::pair<int, int>> &stack,
                               const S21Matrix &graph_matrix) {
  for (int i = graph_matrix.GetCols() - 1; i >= 1; i--) {
    if (graph_matrix(0, i)) stack.Push({0, i});
  }
}

std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                        int startVertex) {
  std::vector<int> res;
  s21::Stack<std::pair<int, int>> stack;
  S21Matrix graph_matrix = graph.GetGraph();
  std::vector<std::vector<bool>> is_white(
      graph_matrix.GetRows(), std::vector<bool>(graph_matrix.GetCols()));

  InitializationVisitVector(is_white, graph_matrix);

  InitializationVertexStack(stack, graph_matrix);

  while (!stack.Empty()) {
    std::pair<int, int> pos = stack.Top();
    stack.Pop();
    if (IsNotVisited(res, pos.first)) res.push_back(pos.first);

    if (is_white[pos.first][pos.second]) {
      is_white[pos.first][pos.second] = false;

      for (int i = graph_matrix.GetCols() - 1; i >= pos.second; i--) {
        stack.Push({pos.second, i});
      }
    }
  }

  auto it = res.begin();
  while (*it != startVertex) {
    res.erase(it);
  }

  return res;
}

std::vector<int> s21::GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                          int startVertex) {
  S21Matrix graph_matrix = graph.GetGraph();
  if (startVertex > graph_matrix.GetRows()) return std::vector<int>();

  std::vector<int> res;
  std::vector<bool> is_visited(graph_matrix.GetRows());

  std::queue<int> q;
  q.push(startVertex);
  is_visited[startVertex] = true;

  while (!q.empty()) {
    int vertex = q.front();
    q.pop();
    res.push_back(vertex);

    for (int i = 0; i < graph_matrix.GetCols(); i++) {
      if (graph_matrix(vertex, i) && !is_visited[i]) {
        q.push(i);
        is_visited[i] = true;
      }
    }
  }

  return res;
}