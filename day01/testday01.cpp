//
// Created by wuggy on 01/12/2017.
//

#include "gtest/gtest.h"

#include "day01.h"

TEST(DAY01, Part1Case1)
{
  auto actual = Day1::solve_part1("1122");
  ASSERT_EQ(actual, 3);
}

TEST(DAY01, Part1Case2)
{
  auto actual = Day1::solve_part1("1111");
  ASSERT_EQ(actual, 4);
}

TEST(DAY01, Part1Case3)
{
  auto actual = Day1::solve_part1("1234");
  ASSERT_EQ(actual, 0);
}

TEST(DAY01, Part1Case4)
{
  auto actual = Day1::solve_part1("91212129");
  ASSERT_EQ(actual, 9);
}

TEST(DAY01, Part2Case1)
{
  auto actual = Day1::solve_part2("1212");
  ASSERT_EQ(actual, 6);
}

TEST(DAY01, Part2Case2)
{
  auto actual = Day1::solve_part2("1221");
  ASSERT_EQ(actual, 0);
}

TEST(DAY01, Part2Case3)
{
  auto actual = Day1::solve_part2("123425");
  ASSERT_EQ(actual, 4);
}

TEST(DAY01, Part2Case4)
{
  auto actual = Day1::solve_part2("123123");
  ASSERT_EQ(actual, 12);
}

TEST(DAY01, Part2Case5)
{
  auto actual = Day1::solve_part2("12131415");
  ASSERT_EQ(actual, 4);
}
