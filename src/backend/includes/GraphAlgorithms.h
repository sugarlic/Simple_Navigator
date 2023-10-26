#ifndef SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H
#define SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H

#include "Graph.h"
#include "s21_queue.h"
#include "s21_stack.h"

namespace s21 {
class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int startVertex);
};
};      // namespace s21
#endif  //  SRC_INCLUDES_S21_GRAPH_ALGORITHMS_H