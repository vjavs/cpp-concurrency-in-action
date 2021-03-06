/*
  Listing 2.5
  Returning a std::thread from a function
*/

#include <thread>

std::thread f() {
  void some_function();
  return std::thread(some_function);
}

std::thread g() {
  void some_other_function(int);
  std::thread t{some_other_function, 42};
  return t;
}

void f(std::thread t);

void h() {
  void some_function();
  f(std::thread{some_function});
  std::thread t{some_function};
  f(std::move(t));
}
