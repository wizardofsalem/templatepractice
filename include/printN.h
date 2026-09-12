#pragma once
#include <iostream>
template <typename LAST> void printN(LAST t) { std::cout << t; }

template <typename T0, typename... T> void printN(T0 t, T... args) {
  std::cout << t;

  printN(args...);
}
