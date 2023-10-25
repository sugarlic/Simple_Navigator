#ifndef SRC_INCLUDES_S21_GRAPH_H
#define SRC_INCLUDES_S21_GRAPH_H
#include <string>
#include <vector>

#include "s21_matrix.h"

namespace s21 {
class Graph {
 public:
  Graph(){};
  void LoadGraphFromFile(std::string filename);
  void exportGraphToDot(std::string filename);

 private:
  S21Matrix graph_;
};
};      // namespace s21
#endif  //  SRC_INCLUDES_S21_GRAPH_H