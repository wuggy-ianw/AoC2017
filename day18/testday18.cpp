#include "gtest/gtest.h"
#include "day18.h"

using namespace Day18;

TEST(DAY18, TestExample1)
{
  state st;
  reg a = 0;

  // Day18::instruction_list instructions;
  std::array<std::unique_ptr<Day18::instruction>, 10> instructions_array
    {
        set(a,1),
        add(a,2),
        mul(a,a),
        mod(a,5),
        snd(a),
        set(a,0),
        rcv(a),
        jgz(a,-1),
        set(a,1),
        jgz(a,-2)
    };

  // make a bloody vector out of it
  instruction_list instructions;
  for(auto& i : instructions_array) instructions.push_back(std::move(i));

  auto breakfunc = [&]{return (st.pc==6 && a>0); };

  ASSERT_EQ(0, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(1, a);

  ASSERT_EQ(1, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(3, a);

  ASSERT_EQ(2, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(9, a);

  ASSERT_EQ(3, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(4, a);

  ASSERT_EQ(4, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(4, st.sound);

  ASSERT_EQ(5, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(0, a);

  ASSERT_EQ(6, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(0, a);

  ASSERT_EQ(7, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(0, a);

  ASSERT_EQ(8, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(1, a);

  ASSERT_EQ(9, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(1, a);

  ASSERT_EQ(7, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_EQ(1, a);

  ASSERT_EQ(6, st.pc);
  Day18::run_step(instructions, st, breakfunc);
  ASSERT_TRUE(st.breakpoint);
}

TEST(DAY18, TestExample2)
{
  state st;
  reg a = 0;

  // Day18::instruction_list instructions;
  std::array<std::unique_ptr<Day18::instruction>, 10> instructions_array
      {
          set(a,1),
          add(a,2),
          mul(a,a),
          mod(a,5),
          snd(a),
          set(a,0),
          rcv(a),
          jgz(a,-1),
          set(a,1),
          jgz(a,-2)
      };

  // make a bloody vector out of it
  instruction_list instructions;
  for(auto& i : instructions_array) instructions.push_back(std::move(i));

  auto breakfunc = [&]{return (st.pc==6 && a>0); };

  ASSERT_EQ(0, st.pc);
  Day18::run(instructions, st, breakfunc);
  ASSERT_TRUE(st.breakpoint);
  ASSERT_EQ(4, st.sound);
}
