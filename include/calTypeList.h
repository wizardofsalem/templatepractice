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
template <IsCalTypeList List> struct back;

template <typename T0> struct back<CalTypeList<T0>> {
  using type = T0;
};

template <typename First, typename... Rest>
struct back<CalTypeList<First, Rest...>> : back<CalTypeList<Rest...>> {};

template <IsCalTypeList List> using back_t = back<List>::type;

static_assert(std::is_same_v<back_t<CalTypeList<int, bool, float>>, float>);

///////////////PUSH_BACK//////////////////////

template <IsCalTypeList List, typename TToPush> struct cal_push_back;

template <typename... Ts, typename LastT>
struct cal_push_back<CalTypeList<Ts...>, LastT> {
  using type = CalTypeList<Ts..., LastT>;
};

template <IsCalTypeList List, typename TToPush>
using cal_push_back_t = cal_push_back<List, TToPush>::type;

static_assert(std::is_same_v<CalTypeList<int, float>,
                             cal_push_back_t<CalTypeList<int>, float>>);

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

template <std::size_t index, IsCalTypeList List> struct is_index_in_range {
  static constexpr bool value = false;
};

/////////////////////////////AT//////////////////////
template <std::size_t index, IsCalTypeList List> struct cal_at {
  using type = cal_at<index - 1, pop_front_t<List>>::type;
};

template <IsCalTypeList List> struct cal_at<0, List> {
  using type = front_t<List>;
};

template <std::size_t index, IsCalTypeList List>
using cal_at_t = cal_at<index, List>::type;

static_assert(std::is_same_v<cal_at<1, CalTypeList<bool, int>>::type, int>);
