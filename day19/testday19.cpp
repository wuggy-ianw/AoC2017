#include "gtest/gtest.h"
#include "day19.h"

TEST(DAY19, TestExample)
{
  std::vector<std::string> path{
      "     |          ",
      "     |  +--+    ",
      "     A  |  C    ",
      " F---|----E|--+ ",
      "     |  |  |  D ",
      "     +B-+  +--+ "};

  std::pair<std::string, int> actual = Day19::solve(path);
  ASSERT_EQ("ABCDEF", actual.first);
  ASSERT_EQ(38, actual.second);
}
