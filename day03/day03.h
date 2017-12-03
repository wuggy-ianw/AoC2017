//
// Created by wuggy on 03/12/2017.
//

#ifndef AOC2017_DAY03_H
#define AOC2017_DAY03_H

#include <cstddef>
#include <utility>
#include <cmath>

namespace Day3
{

  class SpiralIterator
  {
  public:
    int x, y;
    int shell, pos;
    int index;
    int direction;

    static const int directions[4][2];

    SpiralIterator() : x(0), y(0), shell(0), pos(0), index(1), direction(0) {}

    bool atcorner();
    SpiralIterator& next();
  };


  std::size_t solve_part1_directly(std::size_t num);
  int solve_part1(int num);
  int solve_part2(int num);
} // namespace Day3

#endif //AOC2017_DAY03_H
