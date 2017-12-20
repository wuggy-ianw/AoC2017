//
// Created by wuggy on 02/12/2017.
//

#include <fstream>

#include "day02.h"
#include "../utils/aocutils.h"

int main()
{
  std::ifstream ifs("input.txt");
  std::vector< std::vector<std::size_t> > sheet = AOCUtils::parseByLines<std::vector<std::size_t> >(ifs, AOCUtils::parseItem<std::size_t>);

  std::cout << Day2::solve_part1(sheet) << std::endl;
  std::cout << Day2::solve_part2(sheet) << std::endl;

  return 0;
}
