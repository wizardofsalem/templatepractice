#pragma once
#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

// when inheriting from std::false_type, is_tuple now has access to the ::value
// member !
template <typename T> struct is_tuple : std::false_type {};

template <typename... T>
struct is_tuple<std::tuple<T...>> : std::true_type {
}; // partial specialisation on std:::tuple

template <typename T>
concept TupleType = is_tuple<T>::value;

template <typename LAST> void printN(LAST t) { std::cout << t; }

template <typename T0, typename... T> void printN(T0 t, T... args) {
  std::cout << t;

  printN(args...);
}

template <TupleType T, std::size_t... indices>
void print_tuple_impl(T t, std::index_sequence<indices...>) {
  printN(std::get<indices>(t)...);
}

template <TupleType T> void print_tuple(T t) {
  print_tuple_impl(t, std::make_index_sequence<std::tuple_size_v<T>>());
}
