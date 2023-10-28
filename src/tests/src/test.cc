#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "../../s21_graph_algorithms/includes/s21_graph_algorithms.h"
#include "s21_graph.h"
#include "s21_matrix.h"

TEST(Graph_test, test_load_from_file1) {
  EXPECT_ANY_THROW(s21::Graph graph("graph.txt"););
}

TEST(Graph_test, test_load_from_file2) {
  EXPECT_NO_THROW(s21::Graph graph("../../src/examples/graph1.txt"));
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

TEST(Graph_test, djikstra_test_1) {}

TEST(Graph_test, test_export_to_dot_file1) {
  s21::Graph graph("../../src/examples/graph2.txt");
  graph.ExportGraphToDot("../../src/examples/test.dot");

  std::string answer{"graphgraph_name{0--1--3;0--2--5;0--3;1--4;}"};
  std::string test;
  std::ifstream file("../../src/examples/test.dot");

  std::string str;
  while (file >> str) {
    test += str;
  }

  EXPECT_EQ(answer, test);
}

TEST(Graph_test, test_export_to_dot_file2) {
  s21::Graph graph("../../src/examples/or_graph2.txt");
  graph.ExportGraphToDot("../../src/examples/test2.dot");

  std::string answer{
      "graphgraph_name{0->1->3;0->2->5;1->4->5;2->6;2->0;6->"
      "2;}"};
  std::string test;
  std::ifstream file("../../src/examples/test2.dot");

  std::string str;
  while (file >> str) {
    test += str;
  }

  EXPECT_EQ(answer, test);
}

TEST(Graph_test, test_DFS1) {
  s21::Graph graph("../../src/examples/graph2.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {0, 1, 3, 4, 2, 5};
  std::vector<int> res = alg.DepthFirstSearch(graph, 0);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_DFS2) {
  s21::Graph graph("../../src/examples/graph2.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {4, 2, 5};
  std::vector<int> res = alg.DepthFirstSearch(graph, 4);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_DFS3) {
  s21::Graph graph("../../src/examples/or_graph1.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {0, 1, 2, 3};
  std::vector<int> res = alg.DepthFirstSearch(graph, 0);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_DFS4) {
  s21::Graph graph("../../src/examples/big_graph.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {0, 1, 4, 5, 2, 3, 6, 8, 7};
  std::vector<int> res = alg.DepthFirstSearch(graph, 0);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_DFS5) {
  s21::Graph graph("../../src/examples/big_graph.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {2, 3, 6, 8, 7};
  std::vector<int> res = alg.DepthFirstSearch(graph, 2);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

int main(int argc, char **argv) {
  std::filesystem::path currentPath = std::filesystem::absolute(argv[0]);
  std::filesystem::path parentFolder = currentPath.parent_path();
  std::filesystem::current_path(parentFolder);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}