#ifndef AOC2017_DAY18_H
#define AOC2017_DAY18_H

#include <vector>
#include <memory>
#include <iostream>
#include <deque>
#include <cassert>

namespace Day18
{
  struct state
  {
    int pid = 0;
    long long pc = 0;
    long long sound = 0;

    bool breakpoint = false;
    bool waiting = false;

    std::deque<long long>* receive_queue = nullptr;
    std::deque<long long>* send_queue = nullptr;

    unsigned int messages_sent = 0;
    unsigned int messages_recieved = 0;
  };

  struct instruction
  {
    virtual ~instruction()=default;
    virtual void operator()(state& s) = 0;
  };

  typedef std::vector<std::unique_ptr<instruction>> instruction_list;

  struct reg
  {
    long long value;

    reg(int v=0) : value(v) {}

    operator long long&() { return value; }
    operator long long() const { return value; }

    void operator=(int v) { value = v; }
  };


  namespace instructions
  {
    template<typename T>
    struct instr_set : public instruction
    {
      reg &dest;
      T src;

      instr_set(reg& dest, T src) : dest(dest), src(src) {}
      inline void operator()(state& s) { dest = src; s.pc++;}
    };

    template<typename T>
    struct instr_add : public instruction
    {
      reg &dest;
      T src;

      instr_add(reg& dest, T src) : dest(dest), src(src) {}
      inline void operator()(state& s) { dest += src; s.pc++; }
    };

    template<typename T>
    struct instr_mul : public instruction
    {
      reg &dest;
      T src;

      instr_mul(reg& dest, T src) : dest(dest), src(src) {}
      inline void operator()(state& s) { dest *= src; s.pc++; }
    };

    template<typename T>
    struct instr_mod : public instruction
    {
      reg &dest;
      T src;

      instr_mod(reg& dest, T src) : dest(dest), src(src) {}
      inline void operator()(state& s) { dest = dest % src; s.pc++; }
    };

    template<typename testT, typename offsetT>
    struct instr_jgz : public instruction
    {
      testT test;
      offsetT offset;

      inline instr_jgz(testT test, offsetT offset) : test(test), offset(offset) {}
      inline void operator()(state& s) { if (test>0) s.pc+=offset; else s.pc++; }
    };

    template<typename T>
    struct instr_snd : public instruction
    {
      T src;

      instr_snd(T src) : src(src) {}
      inline void operator()(state& s)
      {
        if (s.send_queue==nullptr)
        {
          // part 1
          s.sound = src;
        }
        else
        {
          // part 2!
          s.send_queue->push_back(src);
          s.messages_sent++;
        }

        s.pc++;
      }
    };

    struct instr_rcv : public instruction
    {
      reg& dest;

      inline instr_rcv(reg& dest) : dest(dest) {}
      inline void operator()(state& s)
      {
        if (s.receive_queue == nullptr)
        {
          // part 1
          if (dest != 0) dest = s.sound;
          s.pc++;
        }
        else
        {
          // part 2
          if (!s.receive_queue->empty())
          {
            dest = s.receive_queue->front();
            s.receive_queue->pop_front();
            s.messages_recieved++;
            s.pc++;
            s.waiting = false;
          } else
          {
            s.waiting = true;
          }
        }

        // don't increment pc on every invocation, we want to enter the waiting state if the receive queue is empty
      }
    };

  }

  inline std::unique_ptr<instruction> set(reg& dest, reg& src) { return std::unique_ptr<instruction>(new instructions::instr_set<reg&>(dest, src)); }
  inline std::unique_ptr<instruction> set(reg& dest, long long src) { return std::unique_ptr<instruction>(new instructions::instr_set<long long>(dest, src)); }

  inline std::unique_ptr<instruction> add(reg& dest, reg& src) { return std::unique_ptr<instruction>(new instructions::instr_add<reg&>(dest, src)); }
  inline std::unique_ptr<instruction> add(reg& dest, long long src) { return std::unique_ptr<instruction>(new instructions::instr_add<long long>(dest, src)); }

  inline std::unique_ptr<instruction> mul(reg& dest, reg& src) { return std::unique_ptr<instruction>(new instructions::instr_mul<reg&>(dest, src)); }
  inline std::unique_ptr<instruction> mul(reg& dest, long long src) { return std::unique_ptr<instruction>(new instructions::instr_mul<long long>(dest, src)); }

  inline std::unique_ptr<instruction> mod(reg& dest, reg& src) { return std::unique_ptr<instruction>(new instructions::instr_mod<reg&>(dest, src)); }
  inline std::unique_ptr<instruction> mod(reg& dest, long long src) { return std::unique_ptr<instruction>(new instructions::instr_mod<long long>(dest, src)); }

  inline std::unique_ptr<instruction> jgz(reg& test, int offset) { return std::unique_ptr<instruction>(new instructions::instr_jgz<reg&, long long>(test, offset)); }
  inline std::unique_ptr<instruction> jgz(reg& test, reg& offset) { return std::unique_ptr<instruction>(new instructions::instr_jgz<reg&, reg&>(test, offset)); }
  inline std::unique_ptr<instruction> jgz(long long test, int offset) { return std::unique_ptr<instruction>(new instructions::instr_jgz<long long, long long>(test, offset)); }

  inline std::unique_ptr<instruction> snd(reg& src) { return std::unique_ptr<instruction>(new instructions::instr_snd<reg&>(src)); }
  inline std::unique_ptr<instruction> snd(long long src) { return std::unique_ptr<instruction>(new instructions::instr_snd<long long>(src)); }

  inline std::unique_ptr<instruction> rcv(reg& dest) { return std::unique_ptr<instruction>(new instructions::instr_rcv(dest)); }


  bool run_step(const instruction_list& inst_list, state& s, std::function<bool()> check_break);
  void run(const instruction_list& inst_list, state& s, std::function<bool()> check_break);

  instruction_list get_instructions(reg& a, reg& b, reg& f, reg& i, reg& p);

  int solve_part1();
  int solve_part2();
}

#endif //AOC2017_DAY18_H
