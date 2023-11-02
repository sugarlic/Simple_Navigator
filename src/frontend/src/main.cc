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

void PrintIfGraphNotSet() {
    std::cout << "\n\n  [ Graph is not set. Before any operations, please, setup "
                 "graph from file. ]\n\n";
}

bool SetupGraphPath(s21::Graph& graph);
void BFS(s21::Graph& graph, s21::GraphAlgorithms& algos);
void DFS(s21::Graph& graph, s21::GraphAlgorithms& algos);
void ShortestTwoVertices(s21::Graph& graph, s21::GraphAlgorithms& algos);
void ShortestAllVertices(s21::Graph& graph, s21::GraphAlgorithms& algos);
void SpanningTree(s21::Graph& graph, s21::GraphAlgorithms& algos);

void ParseAnswer(const char symbol) {
  static bool is_setuped_graph{false};
  if (symbol < '1' || symbol > '7') return;
  if (symbol != '1' && !is_setuped_graph) {
    PrintIfGraphNotSet();
    return;
  }
  static s21::Graph graph;
  static s21::GraphAlgorithms algos;
  switch (symbol) {
    case '1':
      SetupGraphPath(graph);
      is_setuped_graph = true;
      break;
    case '2':
      BFS(graph, algos);
      break;
    case '3':
      DFS(graph, algos);
      break;
    case '4':
      std::cout << "[ WARNING: Be sure, that graph hasn't negative weights! ]\n";
      ShortestTwoVertices(graph, algos);
      break;
    case '5':
      ShortestAllVertices(graph, algos);
      break;
    case '6':
      std::cout << "[ WARNING: Be sure, that graphs hasn't any orientation! ]\n";
      SpanningTree(graph, algos);
      break;
    case '7':

      break;
  };
}

bool SetupGraphPath(s21::Graph& graph) {
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
  return true;
}

void BFS(s21::Graph& graph, s21::GraphAlgorithms& algos) {
  int start_index{};
  std::cout << "Please, enter the start vertex position: ";
  std::cin >> start_index;
  std::vector<int> result = algos.BreadthFirstSearch(graph, start_index);
  std::cout << "[ ";
  for (auto& element : result) {
    std::cout << element << " ";
  }
  std::cout << "]\n";
}

void DFS(s21::Graph& graph, s21::GraphAlgorithms& algos) {
  int start_index{};
  std::cout << "Please, enter the start vertex position: ";
  std::cin >> start_index;
  std::vector<int> result = algos.DepthFirstSearch(graph, start_index);
  std::cout << "[ ";
  for (auto& element : result) {
    std::cout << element << " ";
  }
  std::cout << "]\n";
}

void ShortestTwoVertices(s21::Graph& graph, s21::GraphAlgorithms& algos) {
  int vertex1{}, vertex2{};
  std::cout << "\t[ Enter two vertex ]: ";
  std::cin >> vertex1 >> vertex2;
  std::cout << "\t[ Answer is: "
            << algos.GetShortestPathBetweenVertices(graph, vertex1, vertex2)
            << "]\n";
}

void ShortestAllVertices(s21::Graph& graph, s21::GraphAlgorithms& algos) {
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