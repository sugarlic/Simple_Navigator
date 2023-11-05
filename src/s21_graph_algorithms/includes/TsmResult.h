#ifndef TSMRESULT_H
#define TSMRESULT_H
#include "vector"
namespace s21 {
struct TsmResult {
  std::vector<int> vertices;
  double distance{};
};
}  // namespace s21

#endif  // TSMRESULT_H