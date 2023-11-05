#ifndef COLONYDATA_H
#define COLONYDATA_H

#include <cmath>
#include <set>
#include <vector>

#include "s21_matrix.h"

namespace s21 {
class ColonyData {
 public:
  std::vector<std::vector<double>> cost;
  std::vector<std::vector<double>> visibility;
  std::vector<std::vector<double>> T;
  int N;
  double t = 0.1;   // evaporation rate
  double t0 = 1.0;  // initial pheromon value
  /**
   * @brief Construct a new Colony Data object
   *
   * @param graph_map City distances map
   * @param e_rate Pheramon evaporation rate
   * @param init_p Initial pheromon value
   */
  ColonyData(const S21Matrix& graph_map, double e_rate, double init_p)
      : t(e_rate), t0(init_p) {
    N = graph_map.GetCols();
    for (int i = 0; i < N; i++) {
      std::vector<double> V(N);
      std::vector<double> t(N);
      std::vector<double> l(N);
      constexpr double EPSI = 1e-6;
      for (int j = 0; j < N; ++j) {
        const auto value = graph_map(i, j);
        V[j] = value;
        t[j] = t0;
        l[j] = (std::abs(V[j]) > EPSI) ? 1 / V[j] : 0.0;
      }
      cost.push_back(V);
      T.push_back(t);
      visibility.push_back(l);
    }
  }

  double CalcTourCost(std::vector<int> C) {
    int l = C.size() - 1;
    double tour_cost = 0.0;
    for (int i = 0; i < l; i++) {
      tour_cost += cost[C[i]][C[i + 1]];
    }
    if (l >= 0) tour_cost += cost[C[l]][C[0]];
    return tour_cost;
  }
};
}  // namespace s21
#endif  // COLONYDATA_H