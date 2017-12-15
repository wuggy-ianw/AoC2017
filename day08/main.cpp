//
// Created by wuggy on 13/12/2017.
//

#include "day08.h"
#include "../utils/aocutils.h"

#include <fstream>


int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<Day8::Instruction> instructions = AOCUtils::parseByLines<Day8::Instruction>(ifs, Day8::Instruction::parse );

  std::pair<int, int> answers = Day8::solve_part1_part2(instructions);
  std::cout << answers.first << std::endl;
  std::cout << answers.second << std::endl;

  return 0;
}
