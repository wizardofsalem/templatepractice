#pragma once

#include <type_traits>

// list index
template <std::size_t i, typename... Rest> struct list_index;

template <typename T0, typename... Rest> struct list_index<0, T0, Rest...> {
  using type = T0;
};

template <std::size_t N, typename T0, typename... Rest>
struct list_index<N, T0, Rest...> : list_index<N - 1, Rest...> {};

// caltypelist
template <typename...> struct CalTypeList {};

// iscaltype
template <typename T> struct is_caltype : std::false_type {};

template <typename... T>
struct is_caltype<CalTypeList<T...>> : std::true_type {};

template <typename T> static constexpr bool is_caltype_v = is_caltype<T>::value;

template <typename T>
concept IsCalTypeList = is_caltype_v<T>;

// empty
template <IsCalTypeList LIST> struct is_empty : std::false_type {};

template <> struct is_empty<CalTypeList<>> : std::true_type {};

template <IsCalTypeList List>
static constexpr bool is_empty_v = is_empty<List>::value;

// front
template <IsCalTypeList T> struct front;

template <typename T0, typename... T1toN>
struct front<CalTypeList<T0, T1toN...>> {
  using type = T0;
};

template <IsCalTypeList T> using front_t = front<T>::type;

// pop front
template <IsCalTypeList T> struct pop_front {};

template <typename T0, typename... Rest>
struct pop_front<CalTypeList<T0, Rest...>> {
  using type = CalTypeList<Rest...>;
};

template <IsCalTypeList T> using pop_front_t = pop_front<T>::type;

// back
template <IsCalTypeList T> struct back {};

template <typename T0, typename... T1toN>
struct back<CalTypeList<T0, T1toN...>> {
  using type = T0;
};

template <typename Search, IsCalTypeList List>
struct cal_contains
    : std::conditional_t<
          is_empty_v<List>, std::false_type,
          std::conditional_t<std::is_same_v<Search, front_t<List>>,
                             std::true_type,
                             cal_contains<Search, pop_front_t<List>>>> {};

template <typename Search>
struct cal_contains<Search, CalTypeList<>> : std::false_type {};

static_assert(
    cal_contains<double, CalTypeList<float, double, int, unsigned int>>());
