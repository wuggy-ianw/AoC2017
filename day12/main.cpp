//
// Created by wuggy on 21/12/2017.
//

#include "day12.h"

#include <iostream>
#include <fstream>
#include <vector>

int main(void)
{
  std::ifstream ifs("input.txt");
  std::map<int, Day12::program> programs = Day12::parse_input(ifs);

  std::cout << Day12::solve_part1(programs) << std::endl;
  std::cout << Day12::solve_part2(programs) << std::endl;
  return 0;
}
