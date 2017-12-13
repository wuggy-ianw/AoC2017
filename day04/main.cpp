//
// Created by wuggy on 06/12/2017.
//

#include <fstream>

#include "day04.h"
#include "../utils/aocutils.h"

int main()
{
  std::ifstream ifs("input.txt");
  std::vector<std::string> passphrases = AOCUtils::parseByLines<std::string>(ifs, [](const std::string& s) -> std::string { return s;} );

  std::cout << Day4::solve_part1(passphrases) << std::endl;
  std::cout << Day4::solve_part2(passphrases) << std::endl;

  return 0;
}

