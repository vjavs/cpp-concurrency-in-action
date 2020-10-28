/*
  Listing 2.1
  A function that returns while a thread still has access to local variables
 */
#include <thread>

void do_something(int);

struct func {
  int &i_;
  func(int &i) : i_{i} {}
  void operator()() {
    for (unsigned j{0}; j < 1'000'000; ++j) {
      do_something(i_); // Potential access to dangling reference!
    }
  }
};

void oops() {
  int some_local_state{0};
  func my_func{some_local_state};
  std::thread my_thread{my_func};
  my_thread.detach(); // Don't wait for thread to finish
} // New thread might still be running...
