#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include "Ant.h"
#include "ColonyData.h"
#include "TsmResult.h"
#include "limits"
namespace s21 {
class AntColony {
 public:
  int N;                  // number of cities
  int M;                  // number of ants
  std::vector<Ant> ants;  // ants
  double alpha;           // importance of the pheromone level
  double beta;            // importance of the visibility
  ColonyData& d;
  AntColony(double alpha, double beta, ColonyData& data) : d(data) {
    this->alpha = alpha;
    this->beta = beta;
    N = d.N;
    M = d.N;
    for (int i = 0; i < M; i++) {
      Ant a(alpha, beta, d);
      ants.push_back(a);
    }
  }
  void UpdateTourPheramons(std::vector<int> tour) {
    constexpr int Q = 50;
    double tour_cost = d.CalcTourCost(tour);
    double deposit_amount = Q / tour_cost;
    int l = tour.size() - 1;
    for (int i = 0; i < l; i++) {
      auto& pheramon = d.T[tour[i]][tour[i + 1]];
      pheramon = (1 - d.t) * pheramon + pheramon * deposit_amount;
    }
    if (l >= 0) {
      auto& pheramon = d.T[tour[l]][tour[0]];
      pheramon = (1 - d.t) * pheramon + pheramon * deposit_amount;
    }
  }
  TsmResult Run() {
    std::vector<int> best_tour;
    double min_tour_cost = std::numeric_limits<double>::max();
    for (int n = 0; n < 1000; n++) {
      for (int p = 0; p < (N - 1); p++)
        for (auto& ant : ants) ant.Step();
      for (auto& ant : ants) {
        auto p = ant.trail;
        auto tour_cost = d.CalcTourCost(p);
        if (tour_cost < min_tour_cost) {
          min_tour_cost = tour_cost;
          best_tour = p;
        }
      }
      for (auto& ant : ants) {
        ant.Stop();
      }
      UpdateTourPheramons(best_tour);
    }
    return {best_tour, min_tour_cost};
  }
};

}  // namespace s21
#endif  // ANTCOLONY_H