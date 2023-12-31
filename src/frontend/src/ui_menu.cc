#include "ui_menu.h"

namespace s21 {
void Ui::Init() {
  char symbol{};
  while (symbol != 'q') {
    symbol = this->PrintStartScreen();
    this->ParseAnswers(symbol);
  }
}

char Ui::PrintStartScreen() {
  char symbol{};
  this->ClearScreen();
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
  return std::tolower(symbol);
}

void Ui::ClearScreen() { std::system("clear"); }

void Ui::AwaitScreen(int milliseconds) noexcept {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool SetupGraphPath(s21::Graph& graph);
void BFS(s21::Graph& graph, s21::GraphAlgorithms& algos);
void DFS(s21::Graph& graph, s21::GraphAlgorithms& algos);
void ShortestTwoVertices(s21::Graph& graph, s21::GraphAlgorithms& algos);
void ShortestAllVertices(s21::Graph& graph, s21::GraphAlgorithms& algos);
void SpanningTree(s21::Graph& graph, s21::GraphAlgorithms& algos);
void SalesmanResult(s21::Graph& graph, s21::GraphAlgorithms& algos);

void PrintIfGraphNotSet() {
  std::cout << "\n\n  [ Graph is not set. Before any operations, please, setup "
               "graph from file. ]\n\n";
}

void Ui::ParseAnswers(const char symbol) {
  static bool is_setuped_graph{false};
  if (symbol < '1' || symbol > '7') return;
  if (symbol != '1' && !is_setuped_graph) {
    PrintIfGraphNotSet();
    this->AwaitScreen(1500);
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
      std::cout
          << "[ WARNING: Be sure, that graph hasn't negative weights! ]\n";
      try {
        ShortestTwoVertices(graph, algos);
      } catch (std::invalid_argument& ex) {
        std::cout << "Some error. Type of error is\n\t[ " << ex.what()
                  << " ]\n";
      }
      break;
    case '5':
      std::cout << "[ WARNING: Be sure, that graph hasn't negative cycles! ]\n";
      ShortestAllVertices(graph, algos);
      break;
    case '6':
      std::cout
          << "[ WARNING: Be sure, that graphs hasn't any orientation! ]\n";
      SpanningTree(graph, algos);
      break;
    case '7':
      SalesmanResult(graph, algos);
      break;
  };
  this->AwaitScreen(1500);
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

void SalesmanResult(s21::Graph& graph, s21::GraphAlgorithms& algos) {
  if (graph.IsEmptyGraph()) return;
  auto res = algos.SolveTravelingSalesmanProblem(graph);
  std::cout << "Distance: " << res.distance << "\nVertices:";
  for (auto vert : res.vertices) std::cout << vert << " ";
  std::cout << "\n";
};

}  // namespace s21