/*
  Listing 4.1
  Waiting for data to process with std::condition_variable
*/

#include <condition_variable>
#include <mutex>
#include <queue>

struct data_chunk {};

std::mutex mut;
/* Queue used to pass data between two threads. */
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

bool more_data_to_prepare();
data_chunk prepare_data();
void process(data_chunk);
bool is_last_chunk(data_chunk);

void data_preparation_thread() {
  while (more_data_to_prepare()) {
    data_chunk const data{prepare_data()};
    {
      std::scoped_lock lk{mut};
      data_queue.push(data);
    }
    data_cond.notify_one(); // notify after unlocking the mutex
  }
}

void data_processing_thread() {
  while (true) {
    std::unique_lock lk{mut};
    /* Is there some data ready for processing? */
    data_cond.wait(lk, [] { return !data_queue.empty(); });
    data_chunk data{data_queue.front()};
    data_queue.pop();
    lk.unlock();
    process(data);
    if (is_last_chunk(data))
      break;
  }
}
