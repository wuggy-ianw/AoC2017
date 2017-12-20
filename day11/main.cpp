//
// Created by wuggy on 20/12/2017.
//

#include "day11.h"

#include <iostream>
#include <fstream>
#include <vector>

int main(void)
{
  std::ifstream ifs("input.txt");
  std::vector<std::string> moves = Day11::parse_stream(ifs);

  std::pair<int, int> answer = Day11::solve(moves);
  std::cout << answer.first << std::endl;
  std::cout << answer.second << std::endl;
  return 0;
}
