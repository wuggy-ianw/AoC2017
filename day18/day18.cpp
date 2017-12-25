#include "day18.h"


bool Day18::run_step(const instruction_list& inst_list, state& s, std::function<bool()> check_break)
{
  if (!s.breakpoint) s.breakpoint = check_break();
  if(!s.breakpoint && s.pc >= 0 && s.pc < inst_list.size())
  {
    Day18::instruction& i = *inst_list[s.pc];
    i(s);
  }

  return !s.breakpoint && s.pc >= 0 && s.pc < inst_list.size() && !s.waiting;
}

void Day18::run(const instruction_list& inst_list, state& s, std::function<bool()> check_break)
{
  while(run_step(inst_list, s, check_break)) /* keep running run_step */;
}


Day18::instruction_list Day18::get_instructions(Day18::reg& a, Day18::reg& b, Day18::reg& f, Day18::reg& i, Day18::reg& p)
{
  std::array<std::unique_ptr<Day18::instruction>, 41> instructions_array
  {
      set(i,31),    //00
      set(a,1),     //01
      mul(p,17),    //02
      jgz(p,p),     //03
      mul(a,2),     //04
      add(i,-1),    //05
      jgz(i,-2),    //06
      add(a,-1),    //07
      set(i,127),   //08
      set(p,316),   //09
      mul(p,8505),  //10
      mod(p,a),     //11
      mul(p,129749),//12
      add(p,12345), //13
      mod(p,a),     //14
      set(b,p),     //15
      mod(b,10000), //16
      snd(b),       //17
      add(i,-1),    //18
      jgz(i,-9),    //19
      jgz(a,3),     //20
      rcv(b),       //21
      jgz(b,-1),    //22
      set(f,0),     //23
      set(i,126),   //24
      rcv(a),       //25
      rcv(b),       //26
      set(p,a),     //27
      mul(p,-1),    //28
      add(p,b),     //29
      jgz(p,4),     //30
      snd(a),       //31
      set(a,b),     //32
      jgz(1,3),     //33
      snd(b),       //34
      set(f,1),     //35
      add(i,-1),    //36
      jgz(i,-11),   //37
      snd(a),       //38
      jgz(f,-16),   //39
      jgz(a,-19)    //40
  };

  // make a bloody vector out of it
  instruction_list instructions;
  for(auto& inst : instructions_array) instructions.push_back(std::move(inst));

  return instructions;
}



int Day18::solve_part1()
{
  state st;
  reg a, b, f, i, p;

  auto instructions = get_instructions(a,b,f,i,p);
  auto breakfunc = [&]{return (st.pc==25 && a!=0) || (st.pc==26 && b!=0); };
  Day18::run(instructions, st, breakfunc);

  return st.sound;
}

int Day18::solve_part2()
{
  // set up two states
  // we can't use the same instructions since idiot me made the instructions reference the reg objects directly
  // instead of going through the state object... and I'm too lazy to fix it now
  state st0;
  reg a0, b0, f0, i0, p0(0);
  auto instructions0 = get_instructions(a0,b0,f0,i0,p0);

  state st1;
  st1.pid = 1;
  reg a1, b1, f1, i1, p1(1);
  auto instructions1 = get_instructions(a1,b1,f1,i1,p1);

  // and the pipes between them
  std::deque<long long> pipe_0to1;
  std::deque<long long> pipe_1to0;

  st0.send_queue = &pipe_0to1;
  st0.receive_queue = &pipe_1to0;

  st1.send_queue = &pipe_1to0;
  st1.receive_queue = &pipe_0to1;

  // keep running until nothing runs any more
  while(true)
  {
    bool runnable0 = true;
    bool runnable1 = true;

    while(runnable0) runnable0 = run_step(instructions0, st0, []{return false;});
    while(runnable1) runnable1 = run_step(instructions1, st1, []{return false;});

    // if we're not runnable, and there's no undelivered messages, we're done
    if (!runnable0 && !runnable1 && pipe_0to1.empty() && pipe_1to0.empty()) break;
  }

  return st1.messages_sent;
}
