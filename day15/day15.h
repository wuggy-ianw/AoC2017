//
// Created by wuggy on 23/12/2017.
//

#ifndef AOC2017_DAY15_H
#define AOC2017_DAY15_H


#include <cstdint>

namespace Day15
{

  struct generator
  {
    uint32_t seed;
    uint32_t factor;

    generator(uint32_t seed, uint32_t factor) : seed(seed), factor(factor) {}
    uint32_t next();
  };

  int solve_part1(uint32_t seed_a, uint32_t seed_b);
  int solve_part2(uint32_t seed_a, uint32_t seed_b);

}

#endif //AOC2017_DAY15_H
