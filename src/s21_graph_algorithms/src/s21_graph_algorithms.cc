#include "s21_graph_algorithms.h"

#include <vector>
std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                        int startVertex) {
  auto graph_map = graph.GetGraph();
  auto vertices_count = graph_map.GetCols();
  if (startVertex < 0 || startVertex >= vertices_count) return {startVertex};
  std::vector<int> traversed_vertices;
  std::vector<bool> visited(vertices_count, false);
  s21::Stack<int> stack;
  stack.Push(startVertex);

  while (!stack.Empty()) {
    int current_vertex = stack.Top();
    stack.Pop();
    if (!visited[current_vertex]) {
      traversed_vertices.push_back(current_vertex);
      visited[current_vertex] = true;
      for (int neighbor = 0; neighbor < vertices_count; ++neighbor) {
        if (graph_map(current_vertex, neighbor) && !visited[neighbor]) {
          stack.Push(neighbor);
        }
      }
    }
  }

  return traversed_vertices;
}

int MinDistance(const std::vector<int> &distance,
                const std::vector<bool> &checked, int matrix_size);

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