/*
  Listing 3.5
  A fleshed-out class definition for a thread-safe stack
*/
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception {
  const char *what() const throw();
};

template <typename T> class threadsafe_stack {
private:
  std::stack<T> data;
  mutable std::mutex m;

public:
  threadsafe_stack() {}
  threadsafe_stack(const threadsafe_stack &other) {
    std::scoped_lock lock{other.m};
    data = other.data; // Copy performed in constructor body
  }
  threadsafe_stack &operator=(const threadsafe_stack &) = delete;
  void push(T new_value) {
    std::scoped_lock lock{m};
    data.push(std::move(new_value));
  }
  std::shared_ptr<T> pop() {
    std::scoped_lock lock{m};
    if (data.empty()) // Check for empty before trying to pop value
      throw empty_stack{};
    /* Allocate return value before modifying stack */
    std::shared_ptr<T> const res{std::make_shared<T>(data.top())};
    data.pop();
    return res;
  }
  void pop(T &value) {
    std::scoped_lock lock{m};
    if (data.empty())
      throw empty_stack{};
    value = data.top();
    data.pop();
  }
  bool empty() const {
    std::scoped_lock lock{m};
    return data.empty();
  }
};
