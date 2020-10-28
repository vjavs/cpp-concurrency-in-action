/*
  Listing 2.3
  Using RAII to wait for a thread to complete
*/

#include <thread>

class thread_guard {
  std::thread &t_;

public:
  explicit thread_guard(std::thread &t) : t_{t} {}
  ~thread_guard() {
    if (t_.joinable()) {
      t_.join();
    }
  }
  thread_guard(thread_guard const &) = delete;
  thread_guard &operator=(thread_guard const &) = delete;
};

void do_something(int);

struct func {
  int &i_;
  func(int &i) : i_{i} {}
  void operator()() {
    for (unsigned j{0}; j < 1'000'000; ++j) {
      do_something(i_);
    }
  }
};

void do_something_in_current_thread();

void f() {
  int some_local_state{0};
  func my_func(some_local_state);
  std::thread t{my_func};
  thread_guard g{t};
  do_something_in_current_thread();
}
