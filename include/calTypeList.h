#pragma once

// My implementatino of a std::tuple
//  A little library to mnaipulate type lists
#include <type_traits>
template <typename...> struct CalTypeList {};

template <typename T> struct is_caltype : std::false_type {};

template <typename... T>
struct is_caltype<CalTypeList<T...>> : std::true_type {};

template <typename T>
concept IsCalTypeList = is_caltype<T>::value;

template <IsCalTypeList LIST> struct empty : std::false_type {};

template <> struct empty<CalTypeList<>> : std::true_type {};
