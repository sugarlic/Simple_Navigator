#include "s21_graph.h"
#include "s21_graph_algorithms.h"

int main() {
  s21::Graph graph(
      "/Users/sullustd/Simple_Navigator/src/examples/big_graph.txt");

  s21::GraphAlgorithms alg;
  std::vector<int> v = alg.DepthFirstSearch(graph, 0);

  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i] << ' ';
  }
  return 0;
}