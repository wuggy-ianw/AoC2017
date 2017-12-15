//
// Created by wuggy on 13/12/2017.
//

#include "day07.h"
#include "../utils/aocutils.h"

#include <fstream>


int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<Day7::Program> programs = AOCUtils::parseByLines<Day7::Program>(ifs, Day7::Program::parse );

  Day7::Program& root = make_tree(programs);
  std::cout << root.name << std::endl;  // solution to part 1 is the name of the root program

  std::cout << Day7::solve_part2(root) << std::endl;

  return 0;
}
