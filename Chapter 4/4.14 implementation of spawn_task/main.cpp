/*
  Listing 4.14
  A sample implementation of spawn_task
*/

#include <future>
#include <type_traits>

template <typename F, typename A>
std::future<std::invoke_result_t<F(A &&)>> spawn_task(F &&f, A &&a) {
  using result_type = std::invoke_result_t<F(A &&)>;
  std::packaged_task<result_type(A &&)> task{std::move(f)};
  std::future<result_type> res{task.get_future()};
  std::thread t{std::move(task), std::move(a)};
  t.detach();
  return res;
}
