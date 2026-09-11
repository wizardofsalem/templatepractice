#include <calMap.h>
#include <iostream>
#include <type_traits>

template <typename T> void metaFunc() {
  if constexpr (std::is_integral_v<T>) {
    std::cout << "is of integral type\n";
  } else {
    std::cout << "is not of integral type\n";
  }

  if constexpr (std::is_pointer<T>()) {
    std::cout << "is a pointer\n";
  } else {
    std::cout << "is not a pointer\n";
  }
}

int main() {

  CalMap<int, int> cmapFull{};
  CalMap<int, bool> cmapPartial{};
  CalMap<float, double> cmapPrimaryDef{};

  metaFunc<int>();
  metaFunc<std::string>();
  return 0;
}
