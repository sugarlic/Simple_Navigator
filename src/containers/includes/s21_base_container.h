#ifndef SRC_INCLUDES_S21_BASE_CONTAINER_H
#define SRC_INCLUDES_S21_BASE_CONTAINER_H
template <class T>
class BaseContainer {
 public:
  virtual inline bool Empty() = 0;
  virtual inline size_t Size() = 0;
  virtual void Push(const T& new_element) = 0;
  virtual void Pop() = 0;
};

#endif  //   SRC_INCLUDES_S21_BASE_CONTAINER_H
