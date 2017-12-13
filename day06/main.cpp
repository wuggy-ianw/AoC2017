//
// Created by wuggy on 07/12/2017.
//

#include <vector>
#include <iostream>

#include "day06.h"

int main(void)
{
  std::vector<std::size_t> banks = {14, 0, 15, 12, 11, 11, 3, 5, 1, 6, 8, 4, 9, 1, 8, 4};
  auto result = Day6::solve(banks);
  std::cout << result.first << std::endl;
  std::cout << result.second << std::endl;
  return 0;
}
