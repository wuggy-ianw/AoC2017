//
// Created by wuggy on 20/12/2017.
//


#include "gtest/gtest.h"
#include "day11.h"

TEST(DAY11, TestSolvePart1_1)
{
  std::pair<int,int> actual = Day11::solve(Day11::parse_string("ne,ne,ne"));
  ASSERT_EQ(3, actual.first);
  ASSERT_EQ(3, actual.second);
}

TEST(DAY11, TestSolvePart1_2)
{
  std::pair<int,int> actual = Day11::solve(Day11::parse_string("ne,ne,sw,sw"));
  ASSERT_EQ(0, actual.first);
  ASSERT_EQ(2, actual.second);
}

TEST(DAY11, TestSolvePart1_3)
{
  std::pair<int,int> actual = Day11::solve(Day11::parse_string("ne,ne,s,s"));
  ASSERT_EQ(2, actual.first);
  ASSERT_EQ(2, actual.second);
}

TEST(DAY11, TestSolvePart1_4)
{
  std::pair<int,int> actual = Day11::solve(Day11::parse_string("se,sw,se,sw,sw"));
  ASSERT_EQ(3, actual.first);
  ASSERT_EQ(3, actual.second);
}
