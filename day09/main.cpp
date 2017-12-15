//
// Created by wuggy on 15/12/2017.
//

#include "day09.h"
#include "../utils/aocutils.h"

#include <fstream>
#include <cassert>



int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<std::string> lines = AOCUtils::parseByLines<std::string>(ifs, [](std::string s){return s;} );
  assert(lines.size()==1);

  std::cout << Day9::solve_part1(lines[0]) << std::endl;
  std::cout << Day9::solve_part2(lines[0]) << std::endl;

  return 0;
}
