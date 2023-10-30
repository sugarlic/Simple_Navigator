#include "s21_graph_algorithms.h"

#include <queue>
int MinDistance(const std::vector<int> &distance,
                const std::vector<bool> &checked, int matrix_size);
                
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
                               const S21Matrix &graph_matrix, int startVertex) {
  for (int i = graph_matrix.GetCols() - 1; i >= startVertex; i--) {
    if (graph_matrix(startVertex, i)) stack.Push({startVertex, i});
  }
  if (stack.Empty()) stack.Push({startVertex, 0});
}

std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                        int startVertex) {
  S21Matrix graph_matrix = graph.GetGraph();
  if (startVertex >= graph_matrix.GetRows()) return std::vector<int>();
  std::vector<int> res;
  s21::Stack<std::pair<int, int>> stack;
  std::vector<std::vector<bool>> is_white(
      graph_matrix.GetRows(), std::vector<bool>(graph_matrix.GetCols()));

  InitializationVisitVector(is_white, graph_matrix);

  InitializationVertexStack(stack, graph_matrix, startVertex);

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

  return res;
}

std::vector<int> s21::GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                          int startVertex) {
  S21Matrix graph_matrix = graph.GetGraph();
  if (startVertex >= graph_matrix.GetRows()) return std::vector<int>();

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

int s21::GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph,
                                                         int vertex1,
                                                         int vertex2) {
  auto graph_map = graph.GetGraph();
  int matrix_size = graph_map.GetRows();

  std::vector<int> distance(matrix_size, std::numeric_limits<int>::max());
  distance[vertex1] = 0;
  std::vector<bool> checked(matrix_size, false);

  for (int i = 0; i < matrix_size - 1; ++i) {
    int index = MinDistance(distance, checked, matrix_size);
    checked[index] = true;
    for (int j = 0; j < matrix_size; ++j)
      if (!checked[j] && graph_map(index, j) && distance[index] != INT_MAX &&
          distance[index] + graph_map(index, j) < distance[j])
        distance[j] = distance[index] + graph_map(index, j);
  }

  return distance[vertex2];
}

int MinDistance(const std::vector<int> &distance,
                const std::vector<bool> &checked, int matrix_size) {
  int min = std::numeric_limits<int>::max(), min_index{};

  for (int i = 0; i < matrix_size; ++i)
    if (!checked[i] && distance[i] <= min) min = distance[i], min_index = i;

  return min_index;
}

S21Matrix s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    Graph &graph) {
  auto result = graph.GetGraph();

  int matrix_size = result.GetCols();
  for (int i = 0; i < matrix_size; ++i) {
    for (int j = 0; j < matrix_size; ++j) {
      for (int k = 0; k < matrix_size; ++k) {
        if (result(i, k) && result(k, j) && i != j) {
          if (result(i, k) + result(k, j) < result(i, j) || result(i, j) == 0) {
            result(i, j) = result(i, k) + result(k, j);
          }
        }
      }
    }
  }

  return result;
}

S21Matrix s21::GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
  auto graph_map = graph.GetGraph();
  int matrix_size = graph_map.GetRows();
  std::vector<int> selected(matrix_size, 0);
  selected[0] = true;

  int x{};
  int y{};

  S21Matrix result(matrix_size, matrix_size);
  int no_edge{};
  while (no_edge < matrix_size - 1) {
    int min = std::numeric_limits<int>::max();
    x = 0;
    y = 0;

    for (int i = 0; i < matrix_size; ++i) {
      if (selected[i]) {
        for (int j = 0; j < matrix_size; ++j) {
          if (!selected[j] && graph_map(i, j)) {
            if (min > graph_map(i, j)) {
              min = graph_map(i, j);
              x = i;
              y = j;
            }
          }
        }
      }
    }
    result(x, y) = 1;
    selected[y] = true;
    no_edge++;
  }
  return result;
}

s21::TsmResult s21::GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph &graph) {}