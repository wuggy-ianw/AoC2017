#include "day19.h"
#include "../utils/aocutils.h"

#include <iostream>
#include <fstream>

int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<std::string> path = AOCUtils::parseByLines<std::string>(ifs, [](const std::string& s) -> std::string {return s;});

  std::pair<std::string, int> result = Day19::solve(path);
  std::cout << result.first << std::endl;
  std::cout << result.second << std::endl;
  return 0;
}
