/*
  Listing 4.12
  A sequential implementation of Quicksort
*/

#include <algorithm>
#include <list>

template <typename T> std::list<T> sequential_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }
  std::list<T> result;
  result.splice(begin(result), input, begin(result));
  T const &pivot = *result.begin();

  auto divide_point = std::partition(begin(input), end(input),
                                     [&](T const &t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(end(lower_part), input, begin(input), divide_point);
  auto new_lower(sequential_quick_sort(std::move(lower_part)));
  auto new_higher(sequential_quick_sort(std::move(input)));
  result.splice(end(result), new_higher);
  result.splice(begin(result), new_lower);
  return result;
}
