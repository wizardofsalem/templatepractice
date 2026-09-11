#include <iostream>

template <typename KEY, typename VALUE> struct CalMap {
  CalMap() { std::cout << "primary template definition\n"; }
};

// Partial specialisation, becuase one type has been supplied
template <typename VALUE> struct CalMap<int, VALUE> {
  CalMap() { std::cout << "partial specialisation with KEY = int\n"; }
};

// Full specialisatoin, because both types have been specified
template <> struct CalMap<int, int> {
  CalMap() { std::cout << "full specialisation of KEY=int VALUE=int\n"; }
};
