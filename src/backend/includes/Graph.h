#ifndef SRC_INCLUDES_S21_GRAPH_H
#define SRC_INCLUDES_S21_GRAPH_H
#include <vector>

namespace s21 {
class Graph {
 public:
  Graph(){

  };

 private:
  std::vector<std::vector<int>> not_oriented_graph_;
  std::vector<std::vector<int>> oriented_graph_;
};
};      // namespace s21
#endif  //  SRC_INCLUDES_S21_GRAPH_H