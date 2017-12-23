//
// Created by wuggy on 23/12/2017.
//

#include <array>
#include <bitset>
#include "day14.h"
#include "../day10/day10.h"


int Day14::solve_part1(std::string key)
{
  int bitset_count = 0;
  for(int row=0;row<128;row++)
  {
    Day10::hash_value value = Day10::hash(key + '-' + std::to_string(row));
    bitset_count += __builtin_popcountll(value.high);
    bitset_count += __builtin_popcountll(value.low);
  }

  return bitset_count;
}


namespace
{
  void clear_region(std::array<std::array<bool,128>, 128>& grid, int r, int c)
  {
    if (r<0 || r>127) return;
    if (c<0 || c>127) return;

    if (grid[r][c])
    {
      grid[r][c]=false;
      clear_region(grid, r+1, c);
      clear_region(grid, r-1, c);
      clear_region(grid, r, c+1);
      clear_region(grid, r, c-1);
    }
  }
}

int Day14::solve_part2(std::string key)
{
  // actually populate a grid... just use bools, we'll remove each region as we walk
  std::array<std::array<bool,128>, 128> grid = {false};

  for(int row=0;row<128;row++)
  {
    Day10::hash_value value = Day10::hash(key + '-' + std::to_string(row));
    auto p = grid[row].begin();
    for(uint64_t bit = (1ull << 63); bit>0; bit = (bit >> 1)) *p++ = bool(value.high & bit);
    for(uint64_t bit = (1ull << 63); bit>0; bit = (bit >> 1)) *p++ = bool(value.low & bit);
  }

  // iterate through the rows and columns, clearing any new regions as we encounter them
  int region_count = 0;
  for(int row=0; row<128; row++)
  {
    for (int col=0; col<128; col++)
    {
      if (grid[row][col])
      {
        region_count++;
        clear_region(grid, row, col);
      }
    }
  }

  return region_count;
}
