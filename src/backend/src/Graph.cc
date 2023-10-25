#include "Graph.h"

#include <fstream>

void s21::Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) throw std::invalid_argument("NO FILE");

  int size;
  file >> size;
  graph_.SetRows(size);
  graph_.SetCols(size);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) file >> graph_(i, j);
}

void s21::Graph::ExportGraphToDot(std::string filename) {
  std::ofstream file(filename);

  std::string graph_name{"graph_name"};
  file << "graph " << graph_name << " {\n";

  int rows{graph_.GetCols()};
  int cols{graph_.GetRows()};

  S21Matrix help_graph{graph_};

  for (int i = 0; i < rows; i++) {
    for (int j = i + 1; j < cols; j++) {
      if (help_graph(i, j)) RecursiveVertexSet(file, help_graph, i, j);
    }
  }
  file << "}";
}

void s21::Graph::RecursiveVertexSet(std::ofstream &file, S21Matrix &graph,
                                    int row, int col) {
  graph(row, col) = 0;
  file << row;

  for (int i = 1 + col; i < graph.GetCols(); i++)
    if (graph(col, i)) {
      file << " -> ";
      RecursiveVertexSet(file, graph, col, i);
      return;
    }
  file << " -> " << col << ";\n";
}
