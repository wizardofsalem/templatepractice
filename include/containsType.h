#pragma once
#include <cstddef>
#include <tuple>
#include <type_traits>
template <typename SEARCH, typename TUPLE, size_t start_from = 0>
struct containsType {
  static constexpr bool value = std::conditional_t<
      std::is_same_v<std::tuple_element_t<start_from, TUPLE>, SEARCH>,
      std::true_type,
      std::conditional_t<start_from == std::tuple_size_v<TUPLE> - 1,
                         std::false_type,
                         containsType<SEARCH, TUPLE, start_from + 1>>>::value;
};

template <typename SEARCH> struct containsType<SEARCH, std::tuple<>> {
  static constexpr bool value = false;
};
