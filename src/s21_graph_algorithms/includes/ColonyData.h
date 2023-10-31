#ifndef COLONYDATA_H
#define COLONYDATA_H
#include "cmath"
#include "s21_matrix.h"
#include "set"
#include "vector"
namespace s21 {
class ColonyData {
 public:
  std::vector<std::vector<double>> cost;
  std::vector<std::vector<double>> visibility;
  std::vector<std::vector<double>> T;
  int N;

  ColonyData(const S21Matrix& graph_map) {
    std::vector<double> L, M, U;
    N = graph_map.GetCols();
    cost.push_back(L);
    T.push_back(M);
    visibility.push_back(U);
    for (int i = 0; i < N; i++) {
      std::vector<double> V(N + 1);
      std::vector<double> t(N + 1);
      std::vector<double> l(N + 1);
      for (int j = 1; j <= N; j++) {
        V[j] = graph_map(i, j - 1);
        t[j] = 1.0;
        if (V[j] != 0) {
          l[j] = 1 / V[j];
        }
      }
      cost.push_back(V);
      T.push_back(t);
      visibility.push_back(l);
    }
  }

  double tourCost(std::vector<int> C) {
    int l = C.size();
    double tourCost = 0.0;
    l = l - 1;
    for (int i = 0; i < l; i++) {
      tourCost += cost[C[i]][C[i + 1]];
    }
    tourCost += cost[C[l]][C[0]];
    return tourCost;
  }
};
}  // namespace s21
#endif  // COLONYDATA_H