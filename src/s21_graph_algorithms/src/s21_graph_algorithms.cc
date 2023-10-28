#include "s21_graph_algorithms.h"

bool IsNotVisited(const std::vector<int> &v, int vertex) {
  bool res{true};

  for (int i = 0; i < v.size(); i++) {
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

void VertexStackInitialize(s21::Stack<std::pair<int, int>> &stack,
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

  VertexStackInitialize(stack, graph_matrix);

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