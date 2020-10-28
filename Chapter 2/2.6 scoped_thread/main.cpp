/*
  Listing 2.6
  scoped_thread and example usage
*/

#include <stdexcept>
#include <thread>

class scoped_thread {
  std::thread t_;

public:
  explicit scoped_thread(std::thread t) : t_{std::move(t)} {
    if (!t_.joinable()) {
      throw std::logic_error("No thread");
    }
  }
  ~scoped_thread() { t_.join(); }
  scoped_thread(scoped_thread const &) = delete;
  scoped_thread &operator=(scoped_thread const &) = delete;
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
  scoped_thread t{std::thread{func{some_local_state}}};
  do_something_in_current_thread();
}
