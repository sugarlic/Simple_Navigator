#include "s21_graph_algorithms.h"

std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                        int startVertex) {
//   std::vector<int> res;
//   s21::Stack<int> stack;

//   return res;
}


int minDistance(const std::vector<int>& distance, const std::vector<bool>& checked, int matrix_size);

int s21::GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
    int matrix_size = graph.GetGraph().GetRows();

    std::vector<int> distance(matrix_size, std::numeric_limits<int>::max());
    distance[vertex1] = 0;
    std::vector<bool> checked(matrix_size, false);

    for (int i = 0; i < matrix_size - 1; ++i) {
        int index = minDistance(distance, checked, matrix_size);
        checked[index] = true;
        for (int j = 0; j < matrix_size; ++j)
            if (!checked[j] && graph.GetGraph()(index, j) 
                && distance[index] != INT_MAX
                && distance[index] + graph.GetGraph()(index, j) < distance[j])
                distance[j] = distance[index] + graph.GetGraph()(index, j);
    }
  
    return distance[vertex2];
}

int minDistance(const std::vector<int>& distance, const std::vector<bool>& checked, int matrix_size) {
 
    int min = std::numeric_limits<int>::max(), min_index{};
 
    for (int i = 0; i < matrix_size; ++i)
        if (!checked[i] && distance[i] <= min)
            min = distance[i], min_index = i;
 
    return min_index;
}

S21Matrix s21::GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
    S21Matrix result(graph.GetGraph());

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

S21Matrix s21::GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  int matrix_size = graph.GetGraph().GetRows();
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
              if (!selected[j] && graph.GetGraph()(i, j)) {
                  if (min > graph.GetGraph()(i, j)) {
                      min = graph.GetGraph()(i, j);
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

s21::TsmResult s21::GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
    
}