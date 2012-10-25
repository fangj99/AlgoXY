#include <iostream>
#include <cstdlib>

using namespace std;

struct Empty;

template<int x, typename T> struct List {
  static const int first = x;
  typedef T rest;
};

/* Auxiliaries */
template<typename L> struct Print {
  static void apply() {
    std::cout<<L::first<<" ";
    Print<typename L::rest>::apply();
  }
};

template<> struct Print<Empty> {
  static void apply() { std::cout<<"\n"; }
};

/* Length */

template<typename L> struct Length {
  static const int value = 1 + Length<typename L::rest>::value;
};

template<> struct Length<Empty> {
  static const int value = 0;
};

/* Appending */

template<typename L, int x> struct Append {
  typedef List<L::first, typename Append<typename L::rest, x>::result> result;
};

template<int x> struct Append<Empty, x> {
  typedef List<x, Empty> result;
};

int main(int, char**) {
  typedef List<1, List<2, List<3, Empty> > > Lst;
  std::cout<<Length<Empty>::value<<"\n"<<Length<Lst>::value<<"\n";
  Print<Lst>::apply();
  Print<Append<Lst, 4>::result>::apply();
}