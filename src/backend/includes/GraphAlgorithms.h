#ifndef SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H
#define SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H

#include <limits>

#include "Graph.h"
#include "s21_queue.h"
#include "s21_stack.h"

namespace s21 {

struct TsmResult {
  std::vector<int> vertices;
  double distance{};
};

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int startVertex);
  int getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  S21Matrix getShortestPathsBetweenAllVertices(Graph &graph);
  S21Matrix getLeastSpanningTree(Graph &graph);
  TsmResult solveTravelingSalesmanProblem(Graph &graph);
};
};      // namespace s21
#endif  //  SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H