/*
  Listing 3.11
  Thread-safe lazy initialization using a mutex
*/

#include <memory>
#include <mutex>

struct some_resource {
  void do_something();
};

std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;

void foo() {
  std::unique_lock lk{resource_mutex}; // All threads are serialized here
  /* Only the initialization needs protection */
  if (!resource_ptr) {
    resource_ptr.reset(new some_resource);
  }
  lk.unlock();
  resource_ptr->do_something();
}
