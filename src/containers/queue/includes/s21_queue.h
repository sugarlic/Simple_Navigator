#ifndef SRC_INCLUDES_S21_QUEUE_H
#define SRC_INCLUDES_S21_QUEUE_H

#include <initializer_list>
#include <iostream>

#include "../../cpp_realloc.h"
#include "../../s21_base_container.h"

namespace s21 {
template <typename T>
class Queue : BaseContainer<T> {
 public:
  Queue();
  Queue(std::initializer_list<T> const& items);
  Queue(const Queue& other);
  Queue(Queue&& other);
  ~Queue();

  void operator=(Queue&& q);
  void operator=(Queue& q);

  inline T& Front() const;
  inline T& Back() const;

  inline bool Empty() noexcept override;
  inline size_t Size() noexcept override;

  inline void Push(const T& new_element) override;
  void Pop() override;
  inline void Swap(Queue& q) noexcept;

  template <typename... Args>
  void EmplaceBack(Args&&... args);

 private:
  size_t length{};
  size_t capacity{};
  T* data{};
};
};      // namespace s21
#endif  //  SRC_INCLUDES_S21_QUEUE_H
