#ifndef CPP_REALLOC_H
#define CPP_REALLOC_H

#include <iostream>
template <typename T>
T* CppRealloc(T* old_buffer, int old_size, int new_size) {
  if (old_buffer == nullptr) throw std::invalid_argument("realloc() nullptr");
  T* new_buffer = new T[new_size + 1]{};
  for (int i = 0; i < old_size && i < new_size; i++)
    new_buffer[i] = std::move(old_buffer[i]);
  delete[] old_buffer;
  return new_buffer;
}

#endif  //  CPP_REALLOC_H
