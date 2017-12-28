#include "day24.h"
#include "../utils/aocutils.h"

#include <iostream>
#include <fstream>

int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<Day24::part> parts = AOCUtils::parseByLines<Day24::part>(ifs, Day24::parse_part);

  std::cout << Day24::solve_part1(parts) << std::endl;
  std::cout << Day24::solve_part2(parts) << std::endl;
  return 0;
}
