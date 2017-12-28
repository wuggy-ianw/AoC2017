#include "day22.h"
#include "../utils/aocutils.h"

#include <iostream>
#include <fstream>

int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<std::string> input = AOCUtils::parseByLines<std::string>(ifs, [](const std::string& s)->std::string{return s;});

  Day22::sparse_grid grid;
  auto start_point = Day22::populate_grid(grid, input);

  std::cout << Day22::solve_part1(grid, start_point.first, start_point.second, 10000) << std::endl;
  std::cout << Day22::solve_part2(grid, start_point.first, start_point.second, 10000000) << std::endl;

  return 0;
}
