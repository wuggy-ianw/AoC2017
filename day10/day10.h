//
// Created by wuggy on 17/12/2017.
//

#ifndef AOC2017_DAY10_H
#define AOC2017_DAY10_H

#include <vector>
#include <string>

namespace Day10
{
  void knot(std::size_t length, std::vector<int>& string, std::size_t& pos, std::size_t& skip);
  void knot(const std::vector<std::size_t>& lengths, std::vector<int>& string, std::size_t& pos, std::size_t& skip);

  std::string hash(const std::string& txt);

  int solve_part1(const std::vector<std::size_t>& lengths);
  std::string solve_part2(const std::string& txt);
} // namespace Day10

#endif //AOC2017_DAY10_H
