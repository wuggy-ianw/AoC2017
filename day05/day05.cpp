//
// Created by wuggy on 07/12/2017.
//

#include "day05.h"

std::size_t Day5::solve_part1(std::vector<int> jumps)
{
  std::size_t jumpcount = 0;
  long pos = 0;
  while (pos>=0 && pos<jumps.size())
  {
    pos += jumps[pos]++;
    jumpcount++;
  }

  return jumpcount;
}

std::size_t Day5::solve_part2(std::vector<int> jumps)
{
  std::size_t jumpcount = 0;
  long pos = 0;
  while (pos>=0 && pos<jumps.size())
  {
    int& jmp = jumps[pos];
    pos += jmp;
    jmp += jmp >= 3 ? -1 : 1;
    jumpcount++;
  }

  return jumpcount;
}
