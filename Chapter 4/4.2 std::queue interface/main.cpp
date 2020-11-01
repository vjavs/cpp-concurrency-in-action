/*
  Listing 4.2
  std::queue interface
*/

#include <deque>

template <class T, class Container = std::deque<T>> class queue {
public:
  explicit queue(Container const &);
  explicit queue(Container && = Container{});
  template <class Alloc> explicit queue(Alloc const &);
  template <class Alloc> queue(Container const &, Alloc const &);
  template <class Alloc> queue(Container &&, Alloc const &);
  template <class Alloc> queue(queue &&, Alloc const &);
  void swap(queue &q);
  /* query the state of the whole queue */
  bool empty() const;
  std::size_t size() const;
  /* query the elements of the queue */
  T &front();
  T const &front() const;
  T &back();
  T const &back() const;
  /* modify the queue */
  void push(T const &);
  void push(T &&);
  void pop();
  template <class... Args> void emplace(Args &&... args);
};
