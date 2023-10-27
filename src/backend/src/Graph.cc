#include "Graph.h"

void s21::Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) throw std::invalid_argument("NO FILE");

  int size;
  file >> size;
  graph_.SetRows(size);
  graph_.SetCols(size);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) file >> graph_(i, j);

  is_not_oriented_ = IsNotOriented();
}

void s21::Graph::ExportGraphToDot(std::string filename) {
  std::ofstream file(filename);

  std::string graph_name{"graph_name"};
  file << "graph " << graph_name << " {\n";

  if (is_not_oriented_)
    ExportNotOriented(file);
  else {
    ExportOriented(file);
  }
  file << "}";
}

// private
bool s21::Graph::IsNotOriented() {
  bool res{true};

  for (int i = 0; i < graph_.GetRows(); i++) {
    for (int j = 0; j < graph_.GetCols(); j++) {
      if (graph_(i, j) != graph_(j, i)) res = false;
    }
  }

  return res;
}

void s21::Graph::ExportNotOriented(std::ofstream &file) {
  int rows{graph_.GetCols()};
  int cols{graph_.GetRows()};

  S21Matrix help_graph{graph_};

  for (int i = 0; i < rows; i++) {
    for (int j = i + 1; j < cols; j++) {
      if (help_graph(i, j)) RecursiveVertexSet(file, help_graph, i, j, "-");
    }
  }
}

void s21::Graph::ExportOriented(std::ofstream &file) {
  int rows{graph_.GetCols()};
  int cols{graph_.GetRows()};

  S21Matrix help_graph{graph_};

  for (int i = 0; i < rows; i++) {
    for (int j = i + 1; j < cols; j++) {
      if (help_graph(i, j)) RecursiveVertexSet(file, help_graph, i, j, ">");
    }
  }

  for (int i = 1; i < rows; i++) {
    for (int j = 0; j < i; j++) {
      if (help_graph(i, j)) {
        RecursiveVertexSet(file, help_graph, i, j, ">");
      }
    }
  }
}

void s21::Graph::RecursiveVertexSet(std::ofstream &file, S21Matrix &graph,
                                    int row, int col, std::string sign) {
  graph(row, col) = 0;
  file << row;

  for (int i = 1 + col; i < graph.GetCols(); i++)
    if (graph(col, i)) {
      file << " -" << sign << " ";
      RecursiveVertexSet(file, graph, col, i, sign);
      return;
    }
  file << " -" << sign << " " << col << ";\n";
}