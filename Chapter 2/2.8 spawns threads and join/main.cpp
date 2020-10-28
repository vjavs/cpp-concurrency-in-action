/*
  Listing 2.8
  Spawns some threads and waits for them to finish
*/

#include <thread>
#include <vector>

void do_work(unsigned);

void f() {
  std::vector<std::thread> threads;
  for (unsigned i{0}; i < 20; ++i) {
    threads.emplace_back(do_work, i); // Spawns threads
  }
  for (auto &entry : threads)
    entry.join(); // Calls join() on each thread  in turn
}
