/*
  Listing 4.3
  The interface of your threadsafe_queue
*/

#include <memory> // std::shared_ptr
template <typename T> class threadsafe_queue {
public:
  threadsafe_queue();
  threadsafe_queue(threadsafe_queue const &);
  /* disallow assignment for simplicity */
  threadsafe_queue &operator=(threadsafe_queue const &) = delete;
  void push(T new_value);
  /* stores the retrieved value in the referenced variable */
  bool try_pop(T &value);
  /* pointer can be set to nullptr if there's no value */
  std::shared_ptr<T> try_pop();
  void wait_and_pop(T &value);
  std::shared_ptr<T> wait_and_pop();
  bool empty() const;
};
