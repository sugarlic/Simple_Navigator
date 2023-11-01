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

TEST(Graph_test, djikstra_test_2) {
  s21::Graph graph("../../src/examples/djikstra_test.txt");
  s21::GraphAlgorithms alg;

  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 1, 8), 5);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 5, 4), -1);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 4, 7), 3);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 2, 9), 3);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 4, 6), 2);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 4, 8), 4);
}

TEST(Graph_test, djikstra_test_3) {
  s21::Graph graph("../../src/examples/djikstra_test_2.txt");
  s21::GraphAlgorithms alg;
  const int NONPATH = -1;
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 1, 6), 2);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 1, 4), 3);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 4, 5), 2);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 4, 1), NONPATH);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 1, 15), 4);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 14, 7), 3);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 19, 3), 3);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 7, 6), 2);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 14, 16), 4);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 1, 18), 5);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 12, 14), 4);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 3, 19), 3);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 13, 2), 6);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 2, 13), 6);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 14, 2), 8);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 5, 1), NONPATH);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 2, 1), NONPATH);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 2, 1), NONPATH);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 7, 13), 3);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 2, 1), NONPATH);
}

TEST(Graph_test, djikstra_test_4_hardest) {
  s21::Graph graph("../../src/examples/djikstra_test_3.txt");
  s21::GraphAlgorithms alg;
  const int NONPATH = -1;
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 20, 1), 9);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 29, 1), 21);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 22, 2), 8);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 5, 2), 7);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 20, 16), 3);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 1, 26), 9);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 20, 1), 9);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 24, 26), NONPATH);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 4, 22), 4);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 29, 2), 19);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 2, 29), 6);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 30, 28), 20);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 20, 28), 9);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 29, 14), 16);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 22, 24), 11);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 28, 26), 10);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 28, 17), 6);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(graph, 1, 5), 2);
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

TEST(Graph_test, tree_test_2) {
  s21::Graph graph("../../src/examples/djikstra_test.txt");
  s21::GraphAlgorithms alg;

  int counter{};
  EXPECT_NO_THROW({
    auto matrix = alg.GetLeastSpanningTree(graph);
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        counter += matrix(i, j);
      }
    }
    EXPECT_EQ(counter, 8);
  });
}

TEST(Graph_test, tree_test_3) {
  s21::Graph graph("../../src/examples/least_tree.txt");
  s21::GraphAlgorithms alg;

  std::vector<std::vector<int>> res {
    {0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 4, 0, 0, 0, 0}, {0, 7, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 1}, 
    {0, 0, 0, 0, 0, 2, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  int counter{};
  EXPECT_NO_THROW({
    auto matrix = alg.GetLeastSpanningTree(graph);
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        EXPECT_EQ(matrix(i, j), res[i][j]);
        counter += matrix(i, j);
      }
    }
    EXPECT_EQ(counter, 18);
  });
}

TEST(Graph_test, tree_test_4) {
  s21::Graph graph("../../src/examples/least_tree_2.txt");
  s21::GraphAlgorithms alg;
  int counter{};
  EXPECT_NO_THROW({
    auto matrix = alg.GetLeastSpanningTree(graph);
    for (int i = 0; i < 19; ++i) {
      for (int j = 0; j < 19; ++j) {
        counter += matrix(i, j);
      }
    }
    EXPECT_EQ(counter, 23);
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