#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include "Ant.h"
#include "ColonyData.h"
#include "TsmResult.h"
namespace s21 {
class AntColony {
 public:
  int N;                 // cities
  int M;                 // no.of ants
  std::vector<Ant> ant;  // ants
  double alpha;          // importance of the pheromone level
  double beta;           // importance of the visibility
  double evaporation;    // evaporation rate
  ColonyData& d;
  AntColony(double alpha, double beta, double evaporation, ColonyData& data)
      : d(data) {
    this->alpha = alpha;
    this->beta = beta;
    this->evaporation = evaporation;
    N = d.N;
    M = 30;  // ants
    for (int i = 0; i < M; i++) {
      Ant a(alpha, beta, d);
      ant.push_back(a);
    }
  }

  TsmResult run() {
    std::vector<int> path;
    double minTour, tourC;
    for (int n = 0; n < 100; n++) {
      for (int p = 0; p < (N - 1); p++) {
        for (int i = 0; i < M; i++) {
          ant[i].step();
        }
      }
      for (int i = 0; i < M; i++) {
        std::vector<int> p = ant[i].stop();
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
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          d.T[i][j] *= evaporation;
        }
      }
    }
    return {path, tourC};
  }
};

}  // namespace s21
#endif  // ANTCOLONY_H