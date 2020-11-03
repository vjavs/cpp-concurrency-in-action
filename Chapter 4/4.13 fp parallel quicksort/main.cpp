/*
  Listing 4.13
  Parallel Quicksort using futures
*/

#include <algorithm>
#include <future>
#include <list>

template <typename T> std::list<T> parallel_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }
  std::list<T> result;
  result.splice(begin(result), input, begin(input));
  T const &pivot = *result.begin();
  auto divide_point = std::partition(begin(input), end(input),
                                     [&](T const &t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(end(lower_part), input, begin(input), divide_point);
  std::future<std::list<T>> new_lower{
      std::async(&parallel_quick_sort<T>, std::move(lower_part))};
  auto new_higher{parallel_quick_sort(std::move(input))};
  result.splice(end(result), new_higher);
  result.splice(begin(result), new_lower.get());
  return result;
}
