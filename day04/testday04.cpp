//
// Created by wuggy on 06/12/2017.
//

#include "gtest/gtest.h"

#include "day04.h"

TEST(DAY04, Part1Case1)
{
  bool actual = Day4::is_valid_part1("aa bb cc dd ee");
  ASSERT_TRUE(actual);
}

TEST(DAY04, Part1Case2)
{
  bool actual = Day4::is_valid_part1("aa bb cc dd aa");
  ASSERT_FALSE(actual);
}

TEST(DAY04, Part1Case3)
{
  bool actual = Day4::is_valid_part1("aa bb cc dd aaa");
  ASSERT_TRUE(actual);
}

TEST(DAY04, Part2Case1)
{
  bool actual = Day4::is_valid_part2("abcde fghij");
  ASSERT_TRUE(actual);
}

TEST(DAY04, Part2Case2)
{
  bool actual = Day4::is_valid_part2("abcde xyz ecdab");
  ASSERT_FALSE(actual);
}

TEST(DAY04, Part2Case3)
{
  bool actual = Day4::is_valid_part2("a ab abc abd abf abj");
  ASSERT_TRUE(actual);
}

TEST(DAY04, Part2Case4)
{
  bool actual = Day4::is_valid_part2("iiii oiii ooii oooi oooo");
  ASSERT_TRUE(actual);
}

TEST(DAY04, Part2Case5)
{
  bool actual = Day4::is_valid_part2("oiii ioii iioi iiio");
  ASSERT_FALSE(actual);
}
