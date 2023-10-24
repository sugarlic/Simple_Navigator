#include "../includes/s21_stack.h"

template <typename T>
s21::Stack<T>::Stack() : length{0}, capacity{6}, data{new T[capacity]{}} {}

template <typename T>
s21::Stack<T>::Stack(std::initializer_list<T> const &items)
    : length{items.size()}, capacity{length + 6}, data{new T[capacity]{}} {
  std::copy(items.begin(), items.end(), data);
}

template <typename T>
s21::Stack<T>::Stack(const s21::Stack<T> &other) {
  if (this != &other) {
    length = other.length;
    capacity = other.capacity;
    data = new T[capacity]{};
    for (size_t i = 0; i < length; i++) data[i] = other.data[i];
  }
}

template <typename T>
s21::Stack<T>::Stack(s21::Stack<T> &&other) {
  if (this != &other) {
    length = 0;
    capacity = 0;
    if (data) delete[] data;
    Swap(other);
  }
}

template <typename T>
s21::Stack<T>::~Stack() {
  length = 0;
  capacity = 0;
  if (data) delete[] data;
}

template <typename T>
void s21::Stack<T>::operator=(Stack<T> &&other) {
  if (this != &other) {
    length = 0;
    capacity = 0;
    if (data) delete[] data;
    data = nullptr;
    Swap(other);
  }
}

template <typename T>
void s21::Stack<T>::operator=(Stack<T> &other) {
  if (this == &other) throw std::invalid_argument("Itself copy");
  if (data) delete[] data;
  length = other.length;
  capacity = other.capacity;
  data = new T[capacity]{};
  for (int i = 0; i < other.length; i++) data[i] = other.data[i];
}

template <typename T>
inline T &s21::Stack<T>::Top() {
  return data[length - 1];
}

template <typename T>
inline bool s21::Stack<T>::Empty() {
  return !length;
}

template <typename T>
inline size_t s21::Stack<T>::Size() {
  return length;
}

template <typename T>
inline void s21::Stack<T>::Push(const T &new_element) {
  if (length == capacity) {
    capacity += 8;
    data = CppRealloc(data, length, capacity);
  }
  data[length++] = new_element;
}

template <typename T>
inline void s21::Stack<T>::Pop() {
  if (length > 0) length--;
}

template <typename T>
inline void s21::Stack<T>::Swap(Stack<T> &other) noexcept {
  if (this != &other) {
    std::swap(length, other.length);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
  }
}

template <typename T>
template <typename... Args>
inline void s21::Stack<T>::EmplaceFront(Args &&...args) {
  Push(T(std::forward<Args>(args)...));
}