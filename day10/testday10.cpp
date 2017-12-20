//
// Created by wuggy on 17/12/2017.
//

#include "gtest/gtest.h"

#include "day10.h"

TEST(DAY10, TestKnotting)
{
  std::vector<int> string={0,1,2,3,4};
  std::size_t pos = 0;
  std::size_t skip = 0;

  Day10::knot(3, string, pos, skip);
  ASSERT_EQ(string, std::vector<int>({2,1,0,3,4}));
  ASSERT_EQ(pos, 3);
  ASSERT_EQ(skip, 1);

  Day10::knot(4, string, pos, skip);
  ASSERT_EQ(string, std::vector<int>({4,3,0,1,2}));
  ASSERT_EQ(pos, 3);
  ASSERT_EQ(skip, 2);

  Day10::knot(1, string, pos, skip);
  ASSERT_EQ(string, std::vector<int>({4,3,0,1,2}));
  ASSERT_EQ(pos, 1);
  ASSERT_EQ(skip, 3);

  Day10::knot(5, string, pos, skip);
  ASSERT_EQ(string, std::vector<int>({3,4,2,1,0}));
  ASSERT_EQ(pos, 4);
  ASSERT_EQ(skip, 4);
}

TEST(DAY10, TestHash1)
{
  std::string h = Day10::hash("");
  ASSERT_EQ(h, "a2582a3a0e66e6e86e3812dcb672a272");
}

TEST(DAY10, TestHash2)
{
  std::string h = Day10::hash("AoC 2017");
  ASSERT_EQ(h, "33efeb34ea91902bb2f59c9920caa6cd");
}

TEST(DAY10, TestHash3)
{
  std::string h = Day10::hash("1,2,3");
  ASSERT_EQ(h, "3efbe78a8d82f29979031a4aa0b16a9d");
}

TEST(DAY10, TestHash4)
{
  std::string h = Day10::hash("1,2,4");
  ASSERT_EQ(h, "63960835bcdc130f0b66d7ff4f6a5a8e");
}
