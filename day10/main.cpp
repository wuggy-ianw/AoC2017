//
// Created by wuggy on 17/12/2017.
//

#include "day10.h"

#include <iostream>
#include <vector>

int main(void)
{
  std::vector<std::size_t> lengths = {199,0,255,136,174,254,227,16,51,85,1,2,22,17,7,192};
  std::cout << Day10::solve_part1(lengths) << std::endl;
  std::cout << Day10::solve_part2("199,0,255,136,174,254,227,16,51,85,1,2,22,17,7,192") << std::endl;

  return 0;
}
