//
// Created by wuggy on 21/12/2017.
//

#ifndef AOC2017_DAY12_H
#define AOC2017_DAY12_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace Day12
{

  struct program
  {
    int id;
    std::vector<int> sibling_ids;

    inline bool operator==(const program& b) const
    {
      return (id == b.id) && (sibling_ids == b.sibling_ids);
    }
  };

  std::map<int, program> parse_input(std::istream& stream);
  int solve_part1(const std::map<int, program>& programs);
  int solve_part2(const std::map<int, program>& programs);
}

#endif //AOC2017_DAY12_H
