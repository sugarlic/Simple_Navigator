#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "../../s21_graph_algorithms/includes/s21_graph_algorithms.h"
#include "s21_graph.h"
#include "s21_graph_algorithms.h"
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

TEST(Graph_test, djikstra_test_1) {
  s21::Graph graph("../../src/examples/graph2.txt");
  s21::GraphAlgorithms alg;

  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 3, 2), 2);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 3, 4), 2);
}

TEST(Graph_test, floyd_uorshell_1) {
  s21::Graph graph("../../src/examples/graph2.txt");
  s21::GraphAlgorithms alg;

  int res[]{0, 1, 1, 1, 2, 2, 1, 0, 2, 1, 1, 3, 1, 2, 0, 2, 3, 1,
            1, 1, 2, 0, 2, 3, 2, 1, 3, 2, 0, 4, 2, 3, 1, 3, 4, 0};
  size_t index{};
  S21Matrix method_result = alg.GetShortestPathsBetweenAllVertices(graph);

  for (int i = 0; i < method_result.GetRows(); ++i) {
    for (int j = 0; j < method_result.GetCols(); ++j) {
      EXPECT_EQ(res[index++], method_result(i, j));
    }
  }
}

TEST(Graph_test, tree_test) {
  s21::Graph graph("../../src/examples/graph1.txt");
  s21::GraphAlgorithms alg;
  std::vector<std::vector<int>> res = {
      {0, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  EXPECT_NO_THROW({
    auto matrix = alg.GetLeastSpanningTree(graph);
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        EXPECT_EQ(matrix(i, j), res[i][j]);
      }
    }
  });
}

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

  std::vector<int> answer = {4};
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

  std::vector<int> answer = {2};
  std::vector<int> res = alg.DepthFirstSearch(graph, 2);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_DFS6) {
  s21::Graph graph("../../src/examples/big_graph.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {3, 6, 8, 7};
  std::vector<int> res = alg.DepthFirstSearch(graph, 3);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_BFS1) {
  s21::Graph graph("../../src/examples/big_graph.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> res = alg.BreadthFirstSearch(graph, 0);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_BFS2) {
  s21::Graph graph("../../src/examples/big_graph.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {3, 6, 7, 8};
  std::vector<int> res = alg.BreadthFirstSearch(graph, 3);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_BFS3) {
  s21::Graph graph("../../src/examples/big_graph.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {2};
  std::vector<int> res = alg.BreadthFirstSearch(graph, 2);

  EXPECT_EQ(answer.size(), res.size());

  for (size_t i = 0; i < answer.size(); i++) {
    EXPECT_EQ(answer[i], res[i]);
  }
}

TEST(Graph_test, test_BFS4) {
  s21::Graph graph("../../src/examples/or_graph1.txt");
  s21::GraphAlgorithms alg;

  std::vector<int> answer = {0, 1, 2, 3};
  std::vector<int> res = alg.BreadthFirstSearch(graph, 0);

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