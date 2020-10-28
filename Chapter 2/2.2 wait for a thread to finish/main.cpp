/*
  Listing 2.2 Waiting for a thread to finish
*/

#include <thread>

void do_something(int);
void do_something_in_current_thread();

struct func {
  int &i_;
  func(int &i) : i_{i} {}
  void operator()() {
    for (unsigned j{0}; j < 1'000'000; ++j) {
      do_something(i_);
    }
  }
};

void f() {
  int some_local_state{0};
  func my_func(some_local_state);
  std::thread t{my_func};
  try {
    do_something_in_current_thread();
  } catch (...) {
    t.join();
    throw;
  }
  t.join();
}
