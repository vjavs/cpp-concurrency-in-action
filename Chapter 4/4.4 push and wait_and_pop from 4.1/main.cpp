/*
  Listing 4.4
  Extracting push() and wait_and_pop() from listing 4.1
*/

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T> class threadsafe_queue {
private:
  std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

public:
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
};

struct data_chunk {};

bool more_data_to_prepare();
data_chunk prepare_data();
void process(data_chunk);
bool is_last_chunk(data_chunk);

threadsafe_queue<data_chunk> data_queue;

void data_preparation_thread() {
  while (more_data_to_prepare()) {
    data_chunk const data{prepare_data()};
    data_queue.push(data);
  }
}

void data_processing_thread() {
  while (true) {
    data_chunk data;
    data_queue.wait_and_pop(data);
    process(data);
    if (is_last_chunk(data))
      break;
  }
}
