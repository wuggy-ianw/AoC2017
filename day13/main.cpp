//
// Created by wuggy on 22/12/2017.
//

#include "day13.h"

#include <iostream>
#include <fstream>
#include <vector>

int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<Day13::sentry> sentries = Day13::parse_sentries(ifs);

  std::cout << Day13::solve_part1(sentries) << std::endl;
  //std::cout << Day13::solve_part2(sentries) << std::endl;
  std::cout << Day13::solve_part2_sensibly(sentries) << std::endl;

  return 0;
}
