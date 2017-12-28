#include "gtest/gtest.h"
#include "day24.h"
#include "../utils/aocutils.h"


TEST(DAY24, TestSolvePart1)
{
  std::istringstream iss("0/2\n"
                         "2/2\n"
                         "2/3\n"
                         "3/4\n"
                         "3/5\n"
                         "0/1\n"
                         "10/1\n"
                         "9/10\n");

  std::vector<Day24::part> parts = AOCUtils::parseByLines<Day24::part>(iss, Day24::parse_part);

  int strength = Day24::solve_part1(parts);
  ASSERT_EQ(strength, 31);
}

TEST(DAY24, TestSolvePart2)
{
  std::istringstream iss("0/2\n"
                         "2/2\n"
                         "2/3\n"
                         "3/4\n"
                         "3/5\n"
                         "0/1\n"
                         "10/1\n"
                         "9/10\n");

  std::vector<Day24::part> parts = AOCUtils::parseByLines<Day24::part>(iss, Day24::parse_part);

  int strength = Day24::solve_part2(parts);
  ASSERT_EQ(strength, 19);
}
