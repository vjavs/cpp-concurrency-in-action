/*
  Listing 3.4
  An outline class definition for a thread-safe stack
*/

#include <exception>
#include <memory>

struct empty_stack : std::exception {
  const char *what() const noexcept;
};

template <typename T> class threadsafe_stack {
public:
  threadsafe_stack();
  threadsafe_stack(const threadsafe_stack &);
  /* Assignment operator is deleted */
  threadsafe_stack &operator=(const threadsafe_stack &) = delete;
  void push(T new_value);
  std::shared_ptr<T> pop();
  void pop(T &value);
  bool empty() const;
};
