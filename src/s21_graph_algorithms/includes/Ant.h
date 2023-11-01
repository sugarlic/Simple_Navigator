#ifndef ANT_H
#define ANT_H
#include "ColonyData.h"
#include "cmath"
#include "random"
#include "set"
#include "vector"
namespace s21 {
class Ant {
 public:
  std::vector<int> trail;
  std::set<int> available;
  double alpha;  // importance of the pheromone level
  double beta;   // importance of the visibility
  int current_city = 0;
  ColonyData& d;
  std::default_random_engine gen;
  std::uniform_real_distribution<> dis{0.0, 1.0};
  Ant(double a, double b, ColonyData& data) : d(data) {
    alpha = a;
    beta = b;
    reset();
  }
  Ant(const Ant& other) : d(other.d) {
    trail = other.trail;
    available = other.available;
    alpha = other.alpha;
    beta = other.beta;
  }
  void reset() {
    trail = std::vector<int>{0};  // reset to nest.
    available = std::set<int>{};
    for (int i = 1; i < d.N; ++i) {
      available.insert(i);
    }
  }
  void UpdatePheramonOfLastCity() {
    auto& pheramon_cell = d.T[current_city][trail.back()];
    double t = (1 - d.t) * pheramon_cell + d.t * d.t0;
    pheramon_cell = t;
  }
  void deposit() {
    double tourCost = d.tourCost(trail);
    int Q = 100;
    double depositAmount = Q / tourCost;
    int l = trail.size();
    l = l - 1;
    for (int i = 0; i < l; i++) {
      d.T[trail[i]][trail[i + 1]] += depositAmount;
    }
    if (l >= 0) d.T[trail[l]][trail[0]] += depositAmount;
  }

  std::vector<int> stop() {
    deposit();
    std::vector<int> temp = trail;
    reset();
    return temp;
  }
  struct ProbBundle {
    int city{};
    double prob{};
    double q0{};
  };
  void step() {
    current_city = trail.back();
    double p_max = 0;
    double p_a = GetAllowedCitiesProbSum();
    double cityHighest = 0;
    std::vector<ProbBundle> pV{};
    for (auto city : available) {
      double p = GetCityMoveProb(city) / p_a;
      if (p > p_max) {
        cityHighest = city;
        p_max = p;
      }

      // gp = GetRand();
      pV.push_back({city, p, 0});
      // if (gp <= p) {  // move
      //   moved = true;
      //   trail.push_back(*i);
      //   available.erase(i);
      //   break;
      // }
    }
    trail.push_back(cityHighest);
    available.erase(cityHighest);
    UpdatePheramonOfLastCity();
    // std::cout << "Probabilities:\n{\n";
    // for (auto& pb : pV) {
    //   std::cout << "city:" << pb.city << "\t p:" << pb.prob
    //             << "\t random:" << pb.q0 << "\n";
    // }
    // std::cout << "}\n";
    // if (!moved) {
    //   // make a move to the highest available prob city
    //   // move to cityHighest
    //   trail.push_back(cityHighest);
    //   available.erase(cityHighest);
    // }
  }
  std::default_random_engine& GetRandGen() {
    static std::default_random_engine gen;
    return gen;
  }
  double GetRand() { return dis(GetRandGen()); }
  double GetCityMoveProb(int city_index) {
    double T = std::pow(d.T[current_city][city_index], alpha);
    double n = std::pow(d.visibility[current_city][city_index], beta);
    return T * n;
  }
  double GetAllowedCitiesProbSum() {
    double norm = 0.0;
    for (auto city : available) {
      norm += GetCityMoveProb(city);
    }
    return norm;
  }
};
}  // namespace s21
#endif  // ANT_H