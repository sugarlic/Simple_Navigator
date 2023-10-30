#include <string>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

void ParseAnswer(const char symbol);

int main() {
  char symbol{};
  while (symbol != 'q') {
    std::cout << "\tSimple Navigator Interface:\n Enter the need symbol\n";
    std::cout << "1. Load graph from file\n";
    std::cout << "2. BFS\n";
    std::cout << "3. DFS\n";
    std::cout << "4. Search shortest path between two vertices\n";
    std::cout << "5. Search shortest path between ALL vertices\n";
    std::cout << "6. Get least spanning tree\n";
    std::cout << "7. Solve Salesman problem\n";
    std::cout << "Enter the \"q\" to exit!\n";
    std::cin >> symbol;
    ParseAnswer(symbol);
    std::cout << "\n\n";
  }

  return 0;
}

void PrintIfGraphNotSet(const s21::Graph& graph) {
  if (graph.IsEmptyGraph())
    std::cout << "\t[ Graph is not set. Before any operations, please, setup "
                 "graph from file. ]\n";
  return;
}

void SetupGraphPath(s21::Graph& graph);
// BFS
// DFS
void ShortestTwoVertices(s21::Graph& graph, s21::GraphAlgorithms& algos);
void ShortestAllVertices(s21::Graph& graph, s21::GraphAlgorithms& algos);
void SpanningTree(s21::Graph& graph, s21::GraphAlgorithms& algos);

void ParseAnswer(const char symbol) {
  if (symbol < '1' || symbol > '7') return;
  static s21::Graph graph;
  static s21::GraphAlgorithms algos;
  switch (symbol) {
    case '1':
      SetupGraphPath(graph);
      break;
    case '2':
      // BFS
      break;
    case '3':
      // DFS
      break;
    case '4':
      ShortestTwoVertices(graph, algos);
      break;
    case '5':
      ShortestAllVertices(graph, algos);
      break;
    case '6':
      SpanningTree(graph, algos);
      break;
    case '7':

      break;
  };
}

void SetupGraphPath(s21::Graph& graph) {
  std::cin.ignore();
  std::cout << "\t[ Enter the path to the file: ]\n";
  std::string path;
  std::getline(std::cin, path);
  try {
    graph.LoadGraphFromFile(path);
  } catch (std::invalid_argument& ia) {
    std::cout << "\t[ " << ia.what() << " ]\n";
  } catch (...) {
    std::cout << "\t[ Sorry. Unknown error. ]";
  }
  std::cout << "\t[ Graph found and successful set! ]\n";
}

/*
  BFS
*/

/*
  DFS
*/

void ShortestTwoVertices(s21::Graph& graph, s21::GraphAlgorithms& algos) {
  int vertex1{}, vertex2{};
  PrintIfGraphNotSet(graph);
  std::cout << "\t[ Enter two vertex ]: ";
  std::cin >> vertex1 >> vertex2;
  std::cout << "\t[ Answer is: "
            << algos.GetShortestPathBetweenVertices(graph, vertex1, vertex2)
            << "]\n";
}

void ShortestAllVertices(s21::Graph& graph, s21::GraphAlgorithms& algos) {
  PrintIfGraphNotSet(graph);
  S21Matrix matrix_result;
  matrix_result = algos.GetShortestPathsBetweenAllVertices(graph);
  for (int i = 0; i < matrix_result.GetRows(); ++i) {
    for (int j = 0; j < matrix_result.GetCols(); ++j) {
      std::cout << matrix_result(i, j) << "\t";
    }
    std::cout << "\n";
  }
}

void SpanningTree(s21::Graph& graph, s21::GraphAlgorithms& algos) {
  PrintIfGraphNotSet(graph);
  S21Matrix matrix_result;
  matrix_result = algos.GetLeastSpanningTree(graph);
  for (int i = 0; i < matrix_result.GetRows(); ++i) {
    for (int j = 0; j < matrix_result.GetCols(); ++j) {
      std::cout << matrix_result(i, j) << "\t";
    }
    std::cout << "\n";
  }
}

/*
  Komi-Voyager
*/