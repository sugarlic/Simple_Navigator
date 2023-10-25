#include "Graph.h"

#include <fstream>

void s21::Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) throw std::invalid_argument("NO FILE");

  int size, num;
  file >> size;
  graph_.SetRows(size);
  graph_.SetCols(size);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) file >> graph_(i, j);
}

// void s21::Graph::exportGraphToDot(std::string filename) {
//   std::ifstream file(filename);
//   if (!file.is_open()) throw std::invalid_argument("NO FILE");

//   std::string graph_name;
//   std::string vertex;
//   std::getline(file, graph_name);

//   int num;
//   while (file >> vertex) {
//     try {
//       num = std::stoi(vertex.c_str());
//     } catch (std::invalid_argument) {
//       continue;
//     }
//     std::cout << num << '\n';
//   }
// }