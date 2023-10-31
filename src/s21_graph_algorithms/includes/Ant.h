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
  ColonyData& d;
  std::random_device rd;
  std::mt19937 gen;

  Ant(double a, double b, ColonyData& data) : d(data) {
    alpha = a;
    beta = b;
    trail.push_back(1);  // always start from the nest (1)
    for (int i = 2; i <= d.N; i++) {
      available.insert(i);
    }
  }
  Ant(const Ant& other) : d(other.d) {
    trail = other.trail;
    available = other.available;
    alpha = other.alpha;
    beta = other.beta;
  }
  void reset() {
    std::vector<int> L;
    L.push_back(1);
    trail = L;  // reset to nest.
    for (int i = 2; i <= d.N; i++) {
      available.insert(i);
    }
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
    d.T[trail[l]][trail[0]] += depositAmount;
  }

  std::vector<int> stop() {
    deposit();
    std::vector<int> temp = trail;
    reset();
    return temp;
  }

  void step() {
    int currentCity = trail.back();
    double norm = probabilityNorm(currentCity);
    double p, gp;
    bool moved = false;
    double highestProb = 0;
    double cityHighest = 0;
    for (std::set<int>::iterator i = available.begin(); i != available.end();
         i++) {
      p = moveProbability(currentCity, *i, norm);
      if (p > highestProb) {
        cityHighest = *i;
        highestProb = p;
      }
      gp = getRand();
      if (gp <= p) {  // move
        moved = true;
        trail.push_back(*i);
        available.erase(i);
        break;
      }
    }
    if (!moved) {
      // make a move to the highest available prob city
      // move to cityHighest
      trail.push_back(cityHighest);
      available.erase(cityHighest);
    }
  }

  double getRand() {
    gen = std::mt19937(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
  }
  double moveProbability(int i, int j, double norm) {
    double p =
        (std::pow(d.T[i][j], alpha)) * (std::pow(d.visibility[i][j], beta));
    p /= norm;
    return p;
  }

  double probabilityNorm(int currentCity) {
    int size = available.size();
    double norm = 0.0;
    for (std::set<int>::iterator i = available.begin(); i != available.end();
         i++) {
      norm += (std::pow(d.T[currentCity][*i], alpha)) *
              (std::pow(d.visibility[currentCity][*i], beta));
    }
    return norm;
  }
};
}  // namespace s21
#endif  // ANT_H