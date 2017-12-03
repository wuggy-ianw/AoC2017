//
// Created by wuggy on 01/12/2017.
//

#include "day02.h"
#include "../utils/aocutils.h"

#include <limits>
#include <algorithm>


std::size_t Day2::solve_part1(const std::vector< std::vector< std::size_t > >& sheet)
{
  std::size_t sum = 0;

  for (auto& line : sheet)
  {
    auto mmpair = std::minmax_element(line.begin(), line.end());
    sum += *mmpair.second - *mmpair.first;
  }

  return sum;
}

std::size_t Day2::solve_part2(const std::vector< std::vector< std::size_t > >& sheet)
{
  std::size_t sum = 0;

  for (auto& line : sheet)
  {
    for (auto i = line.begin(); i != line.end(); i++)
    {
      for (auto j = i+1; j != line.end(); j++)
      {
        auto mmpair = std::minmax(*i, *j);
        auto mmdiv = std::lldiv(mmpair.second, mmpair.first);
        if (mmdiv.rem == 0) sum += mmdiv.quot;
      }
    }
  }

  return sum;
}
