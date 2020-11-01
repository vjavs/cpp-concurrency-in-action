/*
  Listing 4.5
  Full class definition of a thread-safe queue using condition variables
*/

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

template <typename T> class threadsafe_queue {
private:
  mutable std::mutex mut; // mutex must be mutable
  std::queue<T> data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue() = default;
  threadsafe_queue(threadsafe_queue const &other) {
    std::scoped_lock lk{other.mut};
    data_queue = other.data_queue;
  }
  void push(T new_value) {
    std::scoped_lock lk{mut};
    data_queue.push(new_value);
    data_cond.notify_one();
  }
  void wait_and_pop(T &value) {
    std::unique_lock lk{mut};
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
  }
  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock lk{mut};
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    auto res{std::make_shared(data_queue.front())};
    data_queue.pop();
    return res;
  }
  bool try_pop(T &value) {
    std::scoped_lock lk{mut};
    if (data_queue.empty())
      return false;
    value = data_queue.front();
    data_queue.pop();
    return true;
  }
  std::shared_ptr<T> try_pop() {
    std::scoped_lock lk{mut};
    if (data_queue.empty())
      return {};
    auto res{std::make_shared(data_queue.front())};
    data_queue.pop();
    return res;
  }
  bool empty() const {
    std::scoped_lock lk{mut};
    return data_queue.empty();
  }
};
