/*
  Listing 3.10
  Locking one mutex at a time in a comparison operator
*/

#include <mutex>

class Y {
private:
  int some_detail;
  mutable std::mutex m;
  int get_detail() const {
    /* retrieves the value while protecting it with a lock */
    std::scoped_lock lock_a{m};
    return some_detail;
  }

public:
  Y(int sd) : some_detail{sd} {}
  friend bool operator==(Y const &lhs, Y const &rhs) {
    if (&lhs == &rhs)
      return true;
    int const lhs_value{lhs.get_detail()};
    int const rhs_value{rhs.get_detail()};
    return lhs_value == rhs_value;
  }
};
