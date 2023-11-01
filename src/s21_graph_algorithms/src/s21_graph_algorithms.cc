#include "s21_graph_algorithms.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <set>
#include <vector>

#include "AntColony.h"
namespace s21 {

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

void InitializationVertexStack(Stack<std::pair<int, int>> &stack,
                               const S21Matrix &graph_matrix, int startVertex) {
  for (int i = graph_matrix.GetCols() - 1; i >= startVertex; i--) {
    if (graph_matrix(startVertex, i)) stack.Push({startVertex, i});
  }
  if (stack.Empty()) stack.Push({startVertex, 0});
}

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int startVertex) {
  S21Matrix graph_matrix = graph.GetGraph();
  if (startVertex >= graph_matrix.GetRows()) return std::vector<int>();
  std::vector<int> res;
  Stack<std::pair<int, int>> stack;
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

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
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

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
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

S21Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
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

S21Matrix GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
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

// TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
//     Graph &graph) {}
TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  // Number of vertices in the graph
  auto graph_map = graph.GetGraph();
  ColonyData data(graph_map, 0.6, 1);
  AntColony colony(1, 6, data);
  auto res = colony.run();
  for (auto &city_index : res.vertices) city_index += 1;
  return res;
  // int num_vertices = graph_map.GetRows();

  // // Initialize the pheromone matrix with small values
  // std::vector<std::vector<double>> pheromone_matrix(
  //     num_vertices, std::vector<double>(num_vertices, 0.01));

  // // Number of ants
  // int num_ants = num_vertices;

  // // Number of iterations
  // int num_iterations = 30;

  // // Best route found so far
  // std::vector<int> best_route;
  // double best_distance = std::numeric_limits<double>::max();

  // // Ant colony algorithm
  // for (int iter = 0; iter < num_iterations; iter++) {
  //   // Construct solutions for each ant
  //   for (int ant = 0; ant < num_ants; ant++) {
  //     std::vector<int> route;
  //     std::vector<bool> visited(num_vertices, false);
  //     int current_vertex = 0;  // Start from vertex 0

  //     // Traverse all vertices
  //     for (int i = 0; i < num_vertices - 1; i++) {
  //       visited[current_vertex] = true;
  //       route.push_back(current_vertex);

  //       // Calculate the probabilities for the next vertex
  //       std::vector<double> probabilities(num_vertices, 0.0);
  //       double total = 0.0;

  //       for (int j = 0; j < num_vertices; j++) {
  //         if (!visited[j]) {
  //           probabilities[j] = pow(pheromone_matrix[current_vertex][j], 1.0)
  //           *
  //                              pow(1.0 / graph_map(current_vertex, j), 5.0);
  //           total += probabilities[j];
  //         }
  //       }

  //       // Select the next vertex based on the probabilities
  //       std::random_device rd;
  //       std::mt19937 gen(rd());
  //       std::uniform_real_distribution<> dis(0.0, total);
  //       double random = dis(gen);

  //       double sum = 0.0;
  //       int next_vertex = -1;

  //       for (int j = 0; j < num_vertices; j++) {
  //         if (!visited[j]) {
  //           sum += probabilities[j];
  //           if (sum >= random) {
  //             next_vertex = j;
  //             break;
  //           }
  //         }
  //       }

  //       current_vertex = next_vertex;
  //     }

  //     // Add the last vertex and return to the starting vertex
  //     route.push_back(current_vertex);
  //     route.push_back(0);

  //     // Calculate the distance of the route
  //     double distance = 0.0;
  //     for (int i = 0; i < num_vertices; i++) {
  //       distance += graph_map(route[i], route[i + 1]);
  //     }

  //     // Update the best route if a shorter route is found
  //     if (distance < best_distance) {
  //       best_route = route;
  //       best_distance = distance;
  //     }
  //   }

  //   // Update the pheromone matrix
  //   double evaporation_rate = 0.2;
  //   double pheromone_deposit = 100.0 / best_distance;

  //   for (int i = 0; i < num_vertices; i++) {
  //     for (int j = 0; j < num_vertices; j++) {
  //       pheromone_matrix[i][j] *= evaporation_rate;
  //     }
  //   }

  //   for (int i = 0; i < num_vertices; i++) {
  //     int from = best_route[i];
  //     int to = best_route[i + 1];
  //     pheromone_matrix[from][to] += pheromone_deposit;
  //     pheromone_matrix[to][from] += pheromone_deposit;
  //   }
  // }
  // return {best_route, best_distance};
}
}  // namespace s21