//
// Created by wuggy on 03/12/2017.
//

#include "gtest/gtest.h"

#include "day03.h"


TEST(DAY03, Part1Case1)
{
  // Data from square 1 is carried 0 steps, since it's at the access port.
  int expected = Day3::solve_part1(1);
  ASSERT_EQ(expected, 0);
}

TEST(DAY03, Part1Case2)
{
  // Data from square 12 is carried 3 steps, such as: down, left, left.
  int expected = Day3::solve_part1(12);
  ASSERT_EQ(expected, 3);
}

TEST(DAY03, Part1Case3)
{
  // Data from square 23 is carried only 2 steps: up twice.
  int expected = Day3::solve_part1(23);
  ASSERT_EQ(expected, 2);
}

TEST(DAY03, Part1Case4)
{
  // Data from square 1024 must be carried 31 steps.
  int expected = Day3::solve_part1(1024);
  ASSERT_EQ(expected, 31);
}

TEST(DAY03, Part2Case1)
{
  int expected = Day3::solve_part2(3);
  ASSERT_EQ(expected, 4);
}

TEST(DAY03, Part2Case2)
{
  int expected = Day3::solve_part2(24);
  ASSERT_EQ(expected, 25);
}

TEST(DAY03, Part2Case3)
{
  int expected = Day3::solve_part2(136);
  ASSERT_EQ(expected, 142);
}

TEST(DAY03, Part2Case4)
{
  int expected = Day3::solve_part2(748);
  ASSERT_EQ(expected, 806);
}
