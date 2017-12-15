//
// Created by wuggy on 13/12/2017.
//

#include "gtest/gtest.h"

#include "day08.h"
#include "../utils/aocutils.h"



TEST(DAY08, TestParse1)
{
  std::string example = "b inc 5 if a > 1\n";
  Day8::Instruction instruction = Day8::Instruction::parse(example);

  ASSERT_EQ(instruction.register_name, "b");
  ASSERT_EQ(instruction.direction, 1);
  ASSERT_EQ(instruction.amount, 5);
  ASSERT_EQ(instruction.test_register, "a");
  ASSERT_TRUE(instruction.test.target<std::greater<int>>());
  ASSERT_EQ(instruction.test_value, 1);
}

TEST(DAY08, TestParse2)
{
  std::string example = "a inc 1 if b < 5\n";
  Day8::Instruction instruction = Day8::Instruction::parse(example);

  ASSERT_EQ(instruction.register_name, "a");
  ASSERT_EQ(instruction.direction, 1);
  ASSERT_EQ(instruction.amount, 1);
  ASSERT_EQ(instruction.test_register, "b");
  ASSERT_TRUE(instruction.test.target<std::less<int>>());
  ASSERT_EQ(instruction.test_value, 5);
}

TEST(DAY08, TestParse3)
{
  std::string example = "c dec -10 if a >= 1\n";
  Day8::Instruction instruction = Day8::Instruction::parse(example);

  ASSERT_EQ(instruction.register_name, "c");
  ASSERT_EQ(instruction.direction, -1);
  ASSERT_EQ(instruction.amount, -10);
  ASSERT_EQ(instruction.test_register, "a");
  ASSERT_TRUE(instruction.test.target<std::greater_equal<int>>());
  ASSERT_EQ(instruction.test_value, 1);
}

TEST(DAY08, TestParse4)
{
  std::string example = "c inc -20 if c == 10\n";
  Day8::Instruction instruction = Day8::Instruction::parse(example);

  ASSERT_EQ(instruction.register_name, "c");
  ASSERT_EQ(instruction.direction, 1);
  ASSERT_EQ(instruction.amount, -20);
  ASSERT_EQ(instruction.test_register, "c");
  ASSERT_TRUE(instruction.test.target<std::equal_to<int>>());
  ASSERT_EQ(instruction.test_value, 10);
}


TEST(DAY08, TestPerform)
{
  Day8::State state;
  ASSERT_EQ(state.largest_register_value, std::numeric_limits<int>::min());

  state.perform(Day8::Instruction::parse("b inc 5 if a > 1"));
  ASSERT_EQ(state.registers["b"], 0);
  ASSERT_EQ(state.largest_register_value, 0);

  state.perform(Day8::Instruction::parse("a inc 1 if b < 5"));
  ASSERT_EQ(state.registers["a"], 1);
  ASSERT_EQ(state.registers["b"], 0);
  ASSERT_EQ(state.largest_register_value, 1);

  state.perform(Day8::Instruction::parse("c dec -10 if a >= 1"));
  ASSERT_EQ(state.registers["c"], 10);
  ASSERT_EQ(state.registers["a"], 1);
  ASSERT_EQ(state.registers["b"], 0);
  ASSERT_EQ(state.largest_register_value, 10);


  state.perform(Day8::Instruction::parse("c inc -20 if c == 10"));
  ASSERT_EQ(state.registers["c"], -10);
  ASSERT_EQ(state.registers["a"], 1);
  ASSERT_EQ(state.registers["b"], 0);
  ASSERT_EQ(state.largest_register_value, 10);
}







