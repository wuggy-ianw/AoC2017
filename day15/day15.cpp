//
// Created by wuggy on 23/12/2017.
//

#include "day15.h"

uint32_t Day15::generator::next()
{
  uint32_t val = uint32_t((uint64_t(seed) * factor) % 2147483647ul);
  seed = val;
  return val;
}

namespace
{
  int solve(uint32_t seed_a, uint32_t seed_b, uint32_t accept_mask_a = 0, uint32_t accept_mask_b = 0, int limit = 40*1000*1000)
  {
    Day15::generator gen_a(seed_a, 16807);
    Day15::generator gen_b(seed_b, 48271);

    int collision_count = 0;
    for (int i = 0; i < limit; i++)
    {
      uint32_t a = gen_a.next();
      if (accept_mask_a != 0) while ((a & accept_mask_a) != 0) a = gen_a.next();

      uint32_t b = gen_b.next();
      if (accept_mask_b != 0) while ((b & accept_mask_b) != 0) b = gen_b.next();

      if ((a & 0xffff) == (b & 0xffff)) collision_count++;
    }

    return collision_count;
  }
}

int Day15::solve_part1(uint32_t seed_a, uint32_t seed_b)
{
  return solve(seed_a, seed_b);
}

int Day15::solve_part2(uint32_t seed_a, uint32_t seed_b)
{
  return solve(seed_a, seed_b, 0x3, 0x7, 5*1000*1000);
}


