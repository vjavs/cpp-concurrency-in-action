#include <algorithm>
#include <list>
#include <mutex>

std::list<int> some_list; // single global variable
std::mutex some_mutex;    // global instance of a mutex

void add_to_list(int new_value) {
  std::scoped_lock guard{some_mutex}; // access becomes mutually exclusive
  some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
  std::scoped_lock guard{some_mutex}; // access becomes mutually exclusive
  return std::find(begin(some_list), end(some_list), value_to_find) !=
         end(some_list);
}
