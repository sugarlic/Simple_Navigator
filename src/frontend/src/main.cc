#include "Graph.h"

int main() {
  s21::Graph graph(
      "/Users/sullustd/Simple_Navigator/src/examples/or_graph2.txt");
  graph.ExportGraphToDot("/Users/sullustd/Simple_Navigator/src/examples/1.dot");
  return 0;
}