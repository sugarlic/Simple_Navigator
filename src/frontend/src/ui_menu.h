#ifndef SIMPLE_NAVIGATOR_SRC_FRONTEND_SRC_UI_MENU_H_
#define SIMPLE_NAVIGATOR_SRC_FRONTEND_SRC_UI_MENU_H_

#include <chrono>
#include <string>
#include <thread>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

class Ui {
 public:
  void Init();

 private:
  char PrintStartScreen();
  inline void ClearScreen();
  void ParseAnswers(const char symbol);
  inline void AwaitScreen(int milliseconds) noexcept;
};

#endif  //  SIMPLE_NAVIGATOR_SRC_FRONTEND_SRC_UI_MENU_H_