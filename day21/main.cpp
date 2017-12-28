#include "day21.h"

#include <iostream>
#include <fstream>

int main(void)
{
  std::fstream ifs("input.txt");
  auto rules = Day21::parse_rules(ifs);
  assert(!rules.empty());

  std::cout << Day21::solve_part1(rules) << std::endl;
  std::cout << Day21::solve_part1(rules, 18) << std::endl;
  return 0;
}
