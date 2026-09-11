#include <calMap.h>
#include <iostream>
#include <type_traits>

template <typename T> struct strip_pointer {
  using type = T;
};

template <typename T> struct strip_pointer<T *> {
  using type = T;
};

template <typename T> void metaFunc() {

  using T_without_pointer = typename strip_pointer<std::decay_t<T>>::type;

  if constexpr (std::is_integral<T_without_pointer>::value) {
    std::cout << "is of integral type\n";
  } else {
    std::cout << "is not of integral type\n";
  }
}
int main() {

  CalMap<int, int> cmapFull{};
  CalMap<int, bool> cmapPartial{};
  CalMap<float, double> cmapPrimaryDef{};

  metaFunc<int>();
  metaFunc<int *>();
  metaFunc<int &>();
  return 0;
}
