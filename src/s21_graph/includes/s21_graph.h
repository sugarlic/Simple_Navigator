#ifndef SRC_INCLUDES_S21_GRAPH_H
#define SRC_INCLUDES_S21_GRAPH_H
#include <fstream>
#include <string>
#include <vector>

#include "s21_matrix.h"

namespace s21 {
class Graph {
 public:
  Graph() = default;
  Graph(std::string filename) { LoadGraphFromFile(filename); };
  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);
  S21Matrix GetGraph() { return graph_; };
  inline bool IsEmptyGraph() const noexcept {
    return (graph_.GetCols() == graph_.GetRows() == 0);
  }

 private:
  S21Matrix graph_;
  bool is_not_oriented_;
  void RecursiveVertexSet(std::ofstream &file, S21Matrix &graph, int row,
                          int col, std::string sign);
  bool IsNotOriented();
  void ExportNotOriented(std::ofstream &file);
  void ExportOriented(std::ofstream &file);
};
};      // namespace s21
#endif  //  SRC_INCLUDES_S21_GRAPH_H