#ifndef AOC2017_DAY25_H
#define AOC2017_DAY25_H

#include <unordered_map>

namespace Day25
{

  struct action
  {
    bool write_val;
    int move;
    char next_state;
  };

  struct conditional_actions
  {
    action when_false;
    action when_true;
  };

  typedef std::unordered_map<char, conditional_actions> state_table;

  int solve_part1(const state_table& states, int iterations);
}

#endif //AOC2017_DAY25_H
