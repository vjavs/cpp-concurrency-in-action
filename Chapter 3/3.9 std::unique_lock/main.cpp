/*
  Listing 3.9
  Using std::lock() and std::unique_lock in a swap operation
  *Note: std::scoped_lock still better option
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
    /* std::defer_lock leaves mutexes unlocked */
    std::unique_lock lock_a{lhs.m, std::defer_lock};
    std::unique_lock lock_b{rhs.m, std::defer_lock};
    std::lock(lock_a, lock_b); // Mutexes are lock here
    swap(lhs.some_detail, rhs.some_detail);
  }
};
