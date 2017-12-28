#ifndef AOC2017_DAY24_H
#define AOC2017_DAY24_H

#include <utility>
#include <vector>
#include <bitset>

namespace Day24
{
  typedef std::pair<int, int> part;

  constexpr int max_parts=64;
  typedef std::bitset<max_parts> parts_used_t;

  part parse_part(const std::string& s);

  struct state
  {
    int strength = 0;
    int end_port = 0;
    int length = 0;
    parts_used_t used;  // one entry per part
  };

  int solve_part1(const std::vector<part>& parts);
  int solve_part2(const std::vector<part>& parts);
}

#endif //AOC2017_DAY24_H
