#include "Graph.h"
#include "s21_matrix.h"

int main() {
  s21::Graph graph;
  graph.LoadGraphFromFile(
      "/Users/sullustd/Simple_Navigator/src/examples/graph1.txt");

  return 0;
}