#include "../includes/s21_queue.h"

template <typename T>
s21::Queue<T>::Queue() : length{}, capacity{6}, data{new T[capacity]{}} {}

template <typename T>
s21::Queue<T>::Queue(std::initializer_list<T> const& items)
    : length{items.size()},
      capacity{items.size() + 6},
      data{new T[capacity]{}} {
  std::copy(items.begin(), items.end(), data);
}

template <typename T>
s21::Queue<T>::Queue(const Queue& q) {
  if (this != &q) {
    *this = q;
  }
}

template <typename T>
s21::Queue<T>::Queue(Queue&& q) {
  if (this != &q) {
    length = 0;
    capacity = 0;
    this->Swap(q);
  }
}

template <typename T>
s21::Queue<T>::~Queue() {
  length = 0;
  capacity = 0;
  if (data) delete[] data;
}

template <typename T>
void s21::Queue<T>::operator=(Queue& q) {
  if (this != &q) {
    length = q.length;
    capacity = q.capacity;
    if (data) delete[] data;
    data = new T[capacity]{};
    for (size_t i = 0; i < length; i++) data[i] = q.data[i];
  }
}

template <typename T>
void s21::Queue<T>::operator=(Queue&& q) {
  if (this != &q) {
    length = 0;
    capacity = 0;
    if (data) delete[] data;
    data = nullptr;
    Swap(q);
  }
}

template <typename T>
inline T& s21::Queue<T>::Front() const {
  return data[0];
}

template <typename T>
inline T& s21::Queue<T>::Back() const {
  return data[length - 1];
}

template <typename T>
inline bool s21::Queue<T>::Empty() noexcept {
  return !length;
}

template <typename T>
inline size_t s21::Queue<T>::Size() noexcept {
  return length;
}

template <typename T>
void s21::Queue<T>::Push(const T& new_element) {
  if (length == capacity) {
    capacity += 8;
    data = CppRealloc(data, length, capacity);
  }
  data[length++] = new_element;
}

template <typename T>
void s21::Queue<T>::Pop() {
  T* new_buffer = new T[length]{};
  std::copy(data + 1, data + length, new_buffer);
  if (data) {
    delete[] data;
    data = nullptr;
  }
  std::swap(data, new_buffer);
  length--;
}

template <typename T>
inline void s21::Queue<T>::Swap(Queue& q) noexcept {
  if (this != &q) {
    std::swap(length, q.length);
    std::swap(capacity, q.capacity);
    std::swap(data, q.data);
  }
}

template <typename T>
template <typename... Args>
inline void s21::Queue<T>::EmplaceBack(Args&&... args) {
  Push(T(std::forward<Args>(args)...));
}
