#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include "Ant.h"
#include "ColonyData.h"
#include "TsmResult.h"
namespace s21 {
class AntColony {
 public:
  int N;                  // cities
  int M;                  // no.of ants
  std::vector<Ant> ants;  // ants
  double alpha;           // importance of the pheromone level
  double beta;            // importance of the visibility
  ColonyData& d;
  AntColony(double alpha, double beta, ColonyData& data) : d(data) {
    this->alpha = alpha;
    this->beta = beta;
    N = d.N;
    M = d.N;  // ants
    for (int i = 0; i < M; i++) {
      Ant a(alpha, beta, d);
      ants.push_back(a);
    }
  }

  TsmResult run() {
    std::vector<int> path;
    double minTour, tourC;
    for (int n = 0; n < 300; n++) {
      for (int p = 0; p < (N - 1); p++) {
        for (int i = 0; i < M; i++) {
          ants[i].step();
        }
      }
      // std::vector<std::vector<int>> ants_trails;
      for (auto& ant : ants) {
        auto p = ant.stop();
        // ants_trails.push_back(p);
        if (!path.size()) {
          path = p;
          minTour = d.tourCost(p);
          continue;
        }
        tourC = d.tourCost(p);
        if (tourC < minTour) {
          minTour = tourC;
          path = p;
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          d.T[i][j] *= (1 - d.t);
        }
      }
    }
    return {path, tourC};
  }
};

}  // namespace s21
#endif  // ANTCOLONY_H