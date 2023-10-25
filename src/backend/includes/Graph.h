#ifndef SRC_INCLUDES_S21_GRAPH_H
#define SRC_INCLUDES_S21_GRAPH_H
#include <string>
#include <vector>

#include "../../containers/matrix/includes/matrix.h"

namespace s21 {
class Graph {
 public:
  Graph(){};
  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);

 private:
  S21Matrix graph_;
  void RecursiveVertexSet(std::ofstream &file, S21Matrix &graph, int row,
                          int col);
};
};      // namespace s21
#endif  //  SRC_INCLUDES_S21_GRAPH_H