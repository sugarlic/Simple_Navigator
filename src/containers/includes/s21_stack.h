#ifndef SRC_INCLUDES_CONTAINERS_S21_STACK_H
#define SRC_INCLUDES_CONTAINERS_S21_STACK_H

#include <initializer_list>
#include <iostream>

#include "cpp_realloc.h"
#include "s21_base_container.h"

namespace s21 {
template <typename T>
class Stack : public BaseContainer<T> {
 public:
  Stack();
  Stack(std::initializer_list<T> const &items);
  Stack(const Stack &other);
  Stack(Stack &&other);
  ~Stack();

  void operator=(Stack<T> &&other);
  void operator=(Stack<T> &other);

  inline T &Top();

  inline bool Empty() override;
  inline size_t Size() override;

  inline void Push(const T &new_element) override;
  inline void Pop() override;
  inline void Swap(Stack<T> &other) noexcept;

  template <typename... Args>
  void EmplaceFront(Args &&...args);

 private:
  size_t length{};
  size_t capacity{};
  T *data{};
};
}  // namespace s21

#endif  //  SRC_INCLUDES_CONTAINERS_S21_STACK_H