/*
  Listing 4.6
  Using std::future to get the return value of an asynchronous task
*/

#include <future>
#include <iostream>

int find_the_answer_to_ltuae();
void do_other_stuff();

int main() {
  std::future the_answer{std::async(find_the_answer_to_ltuae)};
  do_other_stuff();
  std::cout << "The answer is " << the_answer.get() << '\n';
}
