//
// Created by wuggy on 13/12/2017.
//

#include "day08.h"
#include "../utils/aocutils.h"

#include <sstream>
#include <cassert>
#include <algorithm>


namespace
{
  std::less<int> less;
  std::less_equal<int> less_equal;
  std::greater<int> greater;
  std::greater_equal<int> greater_equal;
  std::equal_to<int> equal_to;
  std::not_equal_to<int> not_equal_to;
}

Day8::Instruction Day8::Instruction::parse(const std::string& s)
{
  std::istringstream iss(s);
  Day8::Instruction instruction;

  std::string dir;
  std::string cmp;

  iss >> instruction.register_name
      >> dir
      >> instruction.amount
      >> AOCUtils::literal("if")
      >> instruction.test_register
      >> cmp
      >> instruction.test_value;

  if (dir=="inc") instruction.direction = 1;
  else if (dir=="dec") instruction.direction = -1;
  else assert(false);

  if (cmp==">") instruction.test = greater;
  else if (cmp==">=") instruction.test = greater_equal;
  else if (cmp=="<") instruction.test = less;
  else if (cmp=="<=") instruction.test = less_equal;
  else if (cmp=="==") instruction.test = equal_to;
  else if (cmp=="!=") instruction.test = not_equal_to;
  else assert(false);

  assert(bool(iss));
  return instruction;
}

void Day8::State::perform(const Instruction& instruction)
{
  int& srcreg = registers[instruction.register_name];
  const int& testreg = registers[instruction.test_register];

  if (instruction.test(testreg, instruction.test_value))
  {
    srcreg += instruction.direction * instruction.amount;
  }

  largest_register_value = std::max(srcreg, largest_register_value);
}


std::pair<int,int> Day8::solve_part1_part2(const std::vector<Instruction>& instructions)
{
  State state;

  // run all the instructions
  for (const Instruction& i : instructions)
  {
    state.perform(i);
  }

  auto maxreg = std::max_element(state.registers.begin(), state.registers.end(),
                                 [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
                                 {
                                   return a.second < b.second;
                                 });

  // get the largest stored register value
  return std::make_pair(maxreg->second, state.largest_register_value);
}
