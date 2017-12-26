#include "day20.h"
#include <iostream>
#include <fstream>
#include "../utils/aocutils.h"

int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<Day20::particle> particles = AOCUtils::parseByLines<Day20::particle>(ifs, Day20::parse_particle);

  std::cout << Day20::solve_part1(particles) << std::endl;
  std::cout << Day20::solve_part2(particles) << std::endl;
  return 0;
}
