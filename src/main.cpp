#include <calMap.h>
#include <iostream>
#include <type_traits>
#include <vector>

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

bool runtimeContains(const std::string &s, const std::vector<std::string> &v,
                     size_t startFrom = 0) {
  if (startFrom >= v.size())
    return false;

  if (v[startFrom] != s) {
    return runtimeContains(s, v, startFrom + 1);
  } else {
    return true;
  }
}

int main() {

  CalMap<int, int> cmapFull{};
  CalMap<int, bool> cmapPartial{};
  CalMap<float, double> cmapPrimaryDef{};

  metaFunc<int>();
  metaFunc<int *>();
  metaFunc<int &>();

  std::vector<std::string> vec{"hello", "my", "name", "is", "aimee", "li"};

  auto ret = runtimeContains("my", vec);

  std::cout << "ret value = " << ret << "\n";
  return 0;
}
