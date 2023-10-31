#ifndef SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H
#define SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H

#include <limits>

#include "TsmResult.h"
#include "s21_graph.h"
#include "s21_queue.h"
#include "s21_stack.h"
namespace s21 {
class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int startVertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int startVertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  S21Matrix GetShortestPathsBetweenAllVertices(Graph &graph);
  S21Matrix GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
};
};      // namespace s21
#endif  //  SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H