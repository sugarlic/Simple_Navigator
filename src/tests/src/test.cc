#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "Graph.h"
#include "GraphAlgorithms.h"
#include "s21_matrix.h"

TEST(Graph_test, test_load_from_file1) {
  EXPECT_ANY_THROW(s21::Graph graph("graph.txt"););
}

TEST(Graph_test, test_load_from_file2) {
  EXPECT_NO_THROW(
      s21::Graph graph("../../src/examples/graph1.txt")
        );
}

TEST(Graph_test, test_load_from_file3) {
  s21::Graph graph("../../src/examples/graph1.txt");
  S21Matrix graph_matrix(graph.GetGraph());

  std::vector<std::vector<int>> answer{
      {0, 1, 0, 0}, {1, 0, 1, 1}, {0, 1, 0, 0}, {0, 1, 0, 0}};

  EXPECT_EQ(graph_matrix.GetRows(), answer.size());
  for (int i = 0; i < graph_matrix.GetRows(); i++) {
    for (int j = 0; j < graph_matrix.GetCols(); j++) {
      EXPECT_EQ(graph_matrix(i, j), answer[i][j]);
    }
  }
}

TEST(Graph_test, djikstra_test_1) {
    s21::Graph graph("../../src/examples/graph2.txt");
    s21::GraphAlgorithms alg;
    
    EXPECT_EQ(alg.getShortestPathBetweenVertices(graph, 3, 2), 2);
    EXPECT_EQ(alg.getShortestPathBetweenVertices(graph, 3, 4), 2);
}

TEST(Graph_test, floyd_uorshell_1) {
    s21::Graph graph("../../src/examples/graph2.txt");
    s21::GraphAlgorithms alg;

    int res[] {
        0, 1, 1, 1, 2, 2, 
        1, 0, 2, 1, 1, 3,
        1, 2, 0, 2, 3, 1,
        1, 1, 2, 0, 2, 3,
        2, 1, 3, 2, 0, 4,
        2, 3, 1, 3, 4, 0
    };
    size_t index{};
    S21Matrix method_result = alg.getShortestPathsBetweenAllVertices(graph);

    for (int i = 0; i < method_result.GetRows(); ++i) {
      for (int j = 0; j < method_result.GetCols(); ++j) {
        EXPECT_EQ(res[index++], method_result(i, j));
      }
    }

}


TEST(Graph_test, test_export_to_dot_file1) {
  s21::Graph graph("../../src/examples/graph2.txt");
  graph.ExportGraphToDot(
      "../../src/examples/test.dot");

  std::string answer{"graphgraph_name{0->1->3;0->2->5;0->3;1->4;}"};
  std::string test;
  std::ifstream file("../../src/examples/test.dot");

  std::string str;
  while (file >> str) {
    test += str;
  }

  EXPECT_EQ(answer, test);
}


int main(int argc, char **argv) {
  std::filesystem::path currentPath = std::filesystem::absolute(argv[0]);
  std::filesystem::path parentFolder = currentPath.parent_path();
  std::filesystem::current_path(parentFolder);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}