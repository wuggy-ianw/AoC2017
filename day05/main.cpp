//
// Created by wuggy on 07/12/2017.
//

#include <fstream>

#include "day05.h"
#include "../utils/aocutils.h"

int main()
{
  std::ifstream ifs("input.txt");
  std::vector<int> jumps = AOCUtils::parseByLines<int>(ifs, [](const std::string& s) -> int { return std::stoi(s);} );

  std::cout << Day5::solve_part1(jumps) << std::endl;
  std::cout << Day5::solve_part2(jumps) << std::endl;
  return 0;
}

