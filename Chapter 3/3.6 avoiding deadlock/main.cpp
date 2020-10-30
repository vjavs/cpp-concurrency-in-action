/*
  Listing 3.6
  Using std::scoped_lock in a swap operation
*/

#include <mutex>

class some_big_object {};

void swap(some_big_object &lhs, some_big_object &rhs);

class X {
private:
  some_big_object some_detail;
  std::mutex m;

public:
  X(some_big_object const &sd) : some_detail{sd} {}
  friend void swap(X &lhs, X &rhs) {
    if (&lhs == &rhs)
      return;
    std::scoped_lock lock{lhs.m, rhs.m}; // scoped_lock avoids deadlock
    swap(lhs.some_detail, rhs.some_detail);
  }
};
