//
// Created by wuggy on 13/12/2017.
//

#ifndef AOC2017_DAY08_H
#define AOC2017_DAY08_H

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <limits>

namespace Day8
{

  struct Instruction
  {
    std::string register_name;
    int direction;
    int amount;
    std::string test_register;
    std::function<bool(int,int)> test;
    int test_value;

    static Instruction parse(const std::string& s);
  };

  struct State
  {
    std::map<std::string, int> registers;
    int largest_register_value = std::numeric_limits<int>::min();

    void perform(const Instruction& instruction);
  };

  std::pair<int,int> solve_part1_part2(const std::vector<Instruction>& instructions);

}

#endif //AOC2017_DAY08_H
