#include "gtest/gtest.h"
#include "day25.h"

TEST(DAY25, TestSolvePart1)
{
  Day25::state_table states{
      {'A', { { true,  1, 'B' }, {false, -1, 'B'} } },
      {'B', { { true, -1, 'A' }, {true,   1, 'A'} } }
  };

  int checksum = Day25::solve_part1(states, 6);
  ASSERT_EQ(checksum, 3);
}
