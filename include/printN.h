#pragma once
#include <cstddef>
#include <iostream>
#include <tuple>
#include <utility>
template <typename LAST> void printN(LAST t) { std::cout << t; }

template <typename T0, typename... T> void printN(T0 t, T... args) {
  std::cout << t;

  printN(args...);
}

template <typename TUPLE, std::size_t... indices>
void print_tuple_impl(TUPLE t, std::index_sequence<indices...>) {
  printN(std::get<indices>(t)...);
}

template <typename TUPLE> void print_tuple(TUPLE t) {
  print_tuple_impl(t, std::make_index_sequence<std::tuple_size_v<TUPLE>>());
}
