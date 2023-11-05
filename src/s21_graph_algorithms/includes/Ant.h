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
  struct ProbBundle {
    int city{};
    double prob{};
    double pseudo_prob{};
  };
  std::default_random_engine gen;
  std::uniform_real_distribution<> dis{0.0, 1.0};
  Ant(double a, double b, ColonyData& data) : d(data) {
    alpha = a;
    beta = b;
    Reset();
  }
  Ant(const Ant& other) : d(other.d) {
    trail = other.trail;
    available = other.available;
    alpha = other.alpha;
    beta = other.beta;
  }
  void Reset() {
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
  void Stop() { Reset(); }
  double GetMovePseudoProb(int city) {
    double T = d.T[current_city][city];
    double n = std::pow(d.visibility[current_city][city], beta);
    return T * n;
  }

  void MoveToCity(int city) {
    trail.push_back(city);
    available.erase(city);
  }
  void Step() {
    current_city = trail.back();
    double p_max = 0;
    double p_a = GetAllowedCitiesProbSum();
    double choosen_city = 0;
    std::vector<ProbBundle> pV{};
    for (auto city : available) {
      double p = GetCityMoveProb(city) / p_a;
      if (p > p_max) {
        choosen_city = city;
        p_max = p;
      }
      pV.push_back({city, p, GetMovePseudoProb(city)});
    }
    auto q = GetRand();
    const double q0 = 0.2;  // Constant value for random selection from ACO
    if (q <= q0) {          //
      double max_pseudo_prob = std::numeric_limits<double>::min();
      for (auto& bundle : pV) {
        if (bundle.pseudo_prob > max_pseudo_prob) {
          max_pseudo_prob = bundle.pseudo_prob;
          choosen_city = bundle.city;
        }
      }
    } else {
      for (auto& bundle : pV) {
        if (bundle.prob >= GetRand()) {
          choosen_city = bundle.city;
          break;
        }
      }
    }
    MoveToCity(choosen_city);
    UpdatePheramonOfLastCity();
  }
  void PrintProbBundles(std::vector<ProbBundle> vec) {
    std::cout << "Probabilities:\n{\n";
    for (auto& pb : vec) {
      std::cout << "city:" << pb.city << "\t prob:" << pb.prob
                << "\t pseudo prob:" << pb.pseudo_prob << "\n";
    }
    std::cout << "}\n";
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