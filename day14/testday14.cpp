//
// Created by wuggy on 23/12/2017.
//

#include "gtest/gtest.h"
#include "day14.h"

TEST(DAY14, TestSolvePart1)
{
  int actual = Day14::solve_part1("flqrgnkx");
  ASSERT_EQ(8108, actual);
}

TEST(DAY14, TestSolvePart2)
{
  int actual = Day14::solve_part2("flqrgnkx");
  ASSERT_EQ(1242, actual);
}
