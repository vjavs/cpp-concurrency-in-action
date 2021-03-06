/*
  Listing 3.3
  The interface to the std::stack container adapter
*/

#include <deque>

template <typename T, typename Container = std::deque<T>> class stack {
public:
  explicit stack(const Container &);
  explicit stack(Container && = Container());
  template <class Alloc> explicit stack(const Alloc &);
  template <class Alloc> stack(const Container &, const Alloc &);
  template <class Alloc> stack(Container &&, const Alloc &);
  template <class Alloc> stack(stack &&, const Alloc &);
  bool empty() const;
  std::size_t size() const;
  T &top();
  T const &top() const;
  void push(T const &);
  void push(T &&);
  void pop();
  void swap(stack &&);
  template <class... Args> void emplace(Args &&... args); // C++14
};

int main() {
  stack<int> s;
  void do_something(int);

  /* thread unsafe interface */
  if (!s.empty()) {
    int const value{s.top()};
    /* race condition might occur here */
    s.pop();
    do_something(value);
  }
}
