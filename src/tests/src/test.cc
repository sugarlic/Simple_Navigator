#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <vector>

#include "Graph.h"
#include "s21_matrix.h"

TEST(Graph_test, test_load_from_file1) {
  EXPECT_ANY_THROW(s21::Graph graph("graph.txt"););
}

TEST(Graph_test, test_load_from_file2) {
  EXPECT_NO_THROW(
      s21::Graph graph(
          "/Users/sullustd/Simple_Navigator/src/examples/graph1.txt"););
}

TEST(Graph_test, test_load_from_file3) {
  s21::Graph graph("/Users/sullustd/Simple_Navigator/src/examples/graph1.txt");
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

TEST(Graph_test, test_export_to_dot_file1) {
  s21::Graph graph("/Users/sullustd/Simple_Navigator/src/examples/graph2.txt");
  graph.ExportGraphToDot(
      "/Users/sullustd/Simple_Navigator/src/examples/test.dot");

  std::string answer{"graphgraph_name{0--1--3;0--2--5;0--3;1--4;}"};
  std::string test;
  std::ifstream file("/Users/sullustd/Simple_Navigator/src/examples/test.dot");

  std::string str;
  while (file >> str) {
    test += str;
  }

  EXPECT_EQ(answer, test);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}