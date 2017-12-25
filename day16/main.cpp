#include "day16.h"
#include <iostream>
#include <fstream>

int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<Day16::move> moves = Day16::parse_moves(ifs);

  std::cout << Day16::solve_part1<16>(moves) << std::endl;
  //std::cout << Day16::solve_part2<16>(moves) << std::endl;
  std::cout << Day16::solve_part2_sensibly<16, 1*1000*1000*1000>(moves) << std::endl;
  return 0;
}
