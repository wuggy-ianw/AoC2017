//
// Created by wuggy on 15/12/2017.
//

#include "gtest/gtest.h"

#include "day09.h"
#include "../utils/aocutils.h"

#include <sstream>

TEST(DAY09, TestParseCanceledSequence1)
{
  std::istringstream iss("!a");

  Day9::canceled_sequence ignore_canceled;
  iss >> ignore_canceled;

  ASSERT_TRUE(bool(iss)); // even reaching eof should be fine... should not be reading beyond the end!
  ASSERT_EQ(ignore_canceled.start, 0);
  ASSERT_EQ(ignore_canceled.end, 2);
}

TEST(DAY09, TestParseCanceledSequence2)
{
  std::istringstream iss("");

  Day9::canceled_sequence ignore_canceled;
  iss >> ignore_canceled;

  ASSERT_TRUE(bool(iss)); // even reaching eof should be fine... should not be reading beyond the end!
  ASSERT_EQ(ignore_canceled.start, 0);
  ASSERT_EQ(ignore_canceled.end, 0);
}

TEST(DAY09, TestParseCanceledSequence3)
{
  std::istringstream iss("!!!a!b");

  Day9::canceled_sequence ignore_canceled;
  iss >> ignore_canceled;

  ASSERT_TRUE(bool(iss)); // even reaching eof should be fine... should not be reading beyond the end!
  ASSERT_EQ(ignore_canceled.start, 0);
  ASSERT_EQ(ignore_canceled.end, 6);
}

TEST(DAY09, TestParseCanceledSequence4Failure)
{
  std::istringstream iss("!!!a!b!");  // trailing ! without following character

  Day9::canceled_sequence ignore_canceled;
  iss >> ignore_canceled;

  ASSERT_FALSE(bool(iss)); // should fail for trying to match past EOF
  ASSERT_EQ(ignore_canceled.start, -1);
  ASSERT_EQ(ignore_canceled.end, -1);
}

TEST(DAY09, TestParseGarbage1)
{
  std::istringstream iss("<>");

  Day9::garbage garbage;
  iss >> garbage;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(garbage.start, 0);
  ASSERT_EQ(garbage.end, 2);
}

TEST(DAY09, TestParseGarbage2)
{
  std::istringstream iss("<!>");  // cancelled close, so garbage matcher should fail

  Day9::garbage garbage;
  iss >> garbage;

  ASSERT_FALSE(bool(iss));
  ASSERT_EQ(garbage.start, -1);
  ASSERT_EQ(garbage.end, -1);
}

TEST(DAY09, TestParseGarbage3)
{
  std::istringstream iss("<random characters>");

  Day9::garbage garbage;
  iss >> garbage;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(garbage.start, 0);
  ASSERT_EQ(garbage.end, 19);
}

TEST(DAY09, TestParseGarbage4)
{
  std::istringstream iss("<<<<>");

  Day9::garbage garbage;
  iss >> garbage;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(garbage.start, 0);
  ASSERT_EQ(garbage.end, 5);
}

TEST(DAY09, TestParseGarbage5)
{
  std::istringstream iss("<{!>}>");

  Day9::garbage garbage;
  iss >> garbage;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(garbage.start, 0);
  ASSERT_EQ(garbage.end, 6);
}

TEST(DAY09, TestParseGarbage6)
{
  std::istringstream iss("<!!>");

  Day9::garbage garbage;
  iss >> garbage;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(garbage.start, 0);
  ASSERT_EQ(garbage.end, 4);
}

TEST(DAY09, TestParseGarbage7)
{
  std::istringstream iss("<!!!>>");

  Day9::garbage garbage;
  iss >> garbage;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(garbage.start, 0);
  ASSERT_EQ(garbage.end, 6);
}

TEST(DAY09, TestParseGarbage8)
{
  std::istringstream iss("<{o\"i!a,<{i<a>");

  Day9::garbage garbage;
  iss >> garbage;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(garbage.start, 0);
  ASSERT_EQ(garbage.end, 14);
}

TEST(DAY09, TestParseGroup1)
{
  std::istringstream iss("{}");

  Day9::group group;
  iss >> group;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(group.start, 0);
  ASSERT_EQ(group.end, 2);
  ASSERT_TRUE(group.child_groups.empty());
}

TEST(DAY09, TestParseGroup2)
{
  std::istringstream iss("{{{}}}");

  Day9::group group;
  iss >> group;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(group.start, 0);
  ASSERT_EQ(group.end, 6);
  ASSERT_TRUE(group.child_groups.size()==1);
  ASSERT_TRUE(group.child_groups[0].child_groups.size()==1);
  ASSERT_TRUE(group.child_groups[0].child_groups[0].child_groups.empty());
}

TEST(DAY09, TestParseGroup3)
{
  std::istringstream iss("{{},{}}");

  Day9::group group;
  iss >> group;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(group.start, 0);
  ASSERT_EQ(group.end, 7);
  ASSERT_TRUE(group.child_groups.size()==2);
  ASSERT_TRUE(group.child_groups[0].child_groups.empty());
  ASSERT_TRUE(group.child_groups[1].child_groups.empty());
}

TEST(DAY09, TestParseGroup4)
{
  std::istringstream iss("{{{},{},{{}}}}");

  Day9::group group;
  iss >> group;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(group.start, 0);
  ASSERT_EQ(group.end, 14);
  ASSERT_TRUE(group.child_groups.size()==1);
  ASSERT_TRUE(group.child_groups[0].child_groups.size()==3);
  ASSERT_TRUE(group.child_groups[0].child_groups[0].child_groups.empty());
  ASSERT_TRUE(group.child_groups[0].child_groups[1].child_groups.empty());
  ASSERT_TRUE(group.child_groups[0].child_groups[2].child_groups.size()==1);
  ASSERT_TRUE(group.child_groups[0].child_groups[2].child_groups[0].child_groups.empty());
}

TEST(DAY09, TestParseGroup5)
{
  std::istringstream iss("{<{},{},{{}}>}");

  Day9::group group;
  iss >> group;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(group.start, 0);
  ASSERT_EQ(group.end, 14);
  ASSERT_TRUE(group.child_groups.empty());
}

TEST(DAY09, TestParseGroup6)
{
  std::istringstream iss("{<a>,<a>,<a>,<a>}");

  Day9::group group;
  iss >> group;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(group.start, 0);
  ASSERT_EQ(group.end, 17);
  ASSERT_TRUE(group.child_groups.empty());
}

TEST(DAY09, TestParseGroup7)
{
  std::istringstream iss("{{<a>},{<a>},{<a>},{<a>}}");

  Day9::group group;
  iss >> group;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(group.start, 0);
  ASSERT_EQ(group.end, 25);
  ASSERT_TRUE(group.child_groups.size()==4);
  ASSERT_TRUE(group.child_groups[0].child_groups.empty());
  ASSERT_TRUE(group.child_groups[1].child_groups.empty());
  ASSERT_TRUE(group.child_groups[2].child_groups.empty());
  ASSERT_TRUE(group.child_groups[3].child_groups.empty());
}

TEST(DAY09, TestParseGroup8)
{
  std::istringstream iss("{{<!>},{<!>},{<!>},{<a>}}");

  Day9::group group;
  iss >> group;

  ASSERT_TRUE(bool(iss));
  ASSERT_EQ(group.start, 0);
  ASSERT_EQ(group.end, 25);
  ASSERT_TRUE(group.child_groups.size()==1);
  ASSERT_TRUE(group.child_groups[0].child_groups.empty());
}

TEST(DAY09, TestSolvePart1_1)
{
  int actual = Day9::solve_part1("{}");
  ASSERT_EQ(1, actual);
}

TEST(DAY09, TestSolvePart1_2)
{
  int actual = Day9::solve_part1("{{{}}}");
  ASSERT_EQ(6, actual);
}

TEST(DAY09, TestSolvePart1_3)
{
  int actual = Day9::solve_part1("{{},{}}");
  ASSERT_EQ(5, actual);
}

TEST(DAY09, TestSolvePart1_4)
{
  int actual = Day9::solve_part1("{{{},{},{{}}}}");
  ASSERT_EQ(16, actual);
}

TEST(DAY09, TestSolvePart1_5)
{
  int actual = Day9::solve_part1("{<a>,<a>,<a>,<a>}");
  ASSERT_EQ(1, actual);
}

TEST(DAY09, TestSolvePart1_6)
{
  int actual = Day9::solve_part1("{{<ab>},{<ab>},{<ab>},{<ab>}}");
  ASSERT_EQ(9, actual);
}

TEST(DAY09, TestSolvePart1_7)
{
  int actual = Day9::solve_part1("{{<!!>},{<!!>},{<!!>},{<!!>}}");
  ASSERT_EQ(9, actual);
}

TEST(DAY09, TestSolvePart1_8)
{
  int actual = Day9::solve_part1("{{<a!>},{<a!>},{<a!>},{<ab>}}");
  ASSERT_EQ(3, actual);
}

TEST(DAY09, TestSolvePart2_1)
{
  int actual = Day9::solve_part2("{<>}");
  ASSERT_EQ(0, actual);
}

TEST(DAY09, TestSolvePart2_2)
{
  int actual = Day9::solve_part2("{<random characters>}");
  ASSERT_EQ(17, actual);
}

TEST(DAY09, TestSolvePart2_3)
{
  int actual = Day9::solve_part2("{<<<<>}");
  ASSERT_EQ(3, actual);
}

TEST(DAY09, TestSolvePart2_4)
{
  int actual = Day9::solve_part2("{<{!>}>}");
  ASSERT_EQ(2, actual);
}

TEST(DAY09, TestSolvePart2_5)
{
  int actual = Day9::solve_part2("{<!!>}");
  ASSERT_EQ(0, actual);
}

TEST(DAY09, TestSolvePart2_6)
{
  int actual = Day9::solve_part2("{<!!!>>}");
  ASSERT_EQ(0, actual);
}

TEST(DAY09, TestSolvePart2_7)
{
  int actual = Day9::solve_part2("{<{o\"i!a,<{i<a>}");
  ASSERT_EQ(10, actual);
}
