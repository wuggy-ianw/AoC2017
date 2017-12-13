//
// Created by wuggy on 07/12/2017.
//

#include "gtest/gtest.h"

#include "day05.h"

TEST(DAY05, Part1Case1)
{
  std::vector<int> jumps = {0, 3, 0, 1, -3};
  int actual = Day5::solve_part1(jumps);
  ASSERT_EQ(actual, 5);
}

TEST(DAY05, Part2Case1)
{
  std::vector<int> jumps = {0, 3, 0, 1, -3};
  int actual = Day5::solve_part2(jumps);
  ASSERT_EQ(actual, 10);
}
