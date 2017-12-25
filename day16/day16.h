#ifndef AOC2017_DAY16_H
#define AOC2017_DAY16_H

#include <sstream>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <iostream>


namespace Day16
{

  struct move
  {
    enum
    {
      Unknown,
      Spin,
      Exchange,
      Partner
    } type = Unknown;

    int spin_size = 0;

    int swap_pos1 = 0;
    int swap_pos2 = 0;

    char swap_program1 = 0;
    char swap_program2 = 0;
  };

  template<unsigned int size>
  void perform_move(const move& m, std::array<char, size>& programs)
  {
    switch(m.type)
    {
      case move::Unknown:
      default:
        assert(false);
        break;

      case move::Spin:{
        std::array<char, size> newprograms={};
        auto endp = std::copy(programs.begin() + (size - m.spin_size), programs.end(), newprograms.begin());
        std::copy(programs.begin(), programs.begin() + (size - m.spin_size), endp);
        programs = newprograms;
        break;
      };

      case move::Exchange: {
        std::swap(programs[m.swap_pos1], programs[m.swap_pos2]);
        break;
      }

      case move::Partner: {
        auto a = std::find(programs.begin(), programs.end(), m.swap_program1);
        auto b = std::find(programs.begin(), programs.end(), m.swap_program2);
        std::swap(*a,*b);
        break;
      }
    }
  }

  move parse_move(const std::string& str);
  std::vector<move> parse_moves(std::istream& stream);

  template<unsigned int size>
  void dance(const std::vector<Day16::move>& moves, std::array<char, size>& programs)
  {
    for (const auto& m : moves) perform_move(m, programs);
  }

  template<unsigned int size, unsigned int cycles>
  std::string solve(const std::vector<Day16::move>& moves)
  {
    std::array<char, size> programs;
    std::iota(programs.begin(), programs.end(), 'a');

    for (unsigned int i=0; i<cycles; i++) dance(moves, programs);

    return std::string(programs.begin(), programs.end());
  }

  template<unsigned int size>
  std::string solve_part1(const std::vector<Day16::move>& moves)
  {
    return solve<size, 1>(moves);
  }

  template<unsigned int size>
  std::string solve_part2(const std::vector<Day16::move>& moves)
  {
    return solve<size, 1*1000*1000*1000>(moves);
  }

  template<unsigned int size>
  std::array<char, size> apply_dances(const std::array<char, size>& map, const std::array<char, size>& programs)
  {
    std::array<char, size> newprograms;
    for(int i=0;i<size;i++)
    {
      newprograms[i] = programs[map[i]];
    }
    return newprograms;
  }

  template<unsigned int size>
  std::array<char, size> apply_partners(const std::array<char, size>& map, const std::array<char, size>& programs)
  {
    std::array<char, size> newprograms = programs;
    for(int i=0;i<size;i++)
    {
      const char original = programs[i];
      const char result = map[original - 'a'];

      newprograms[i] = result;
    }
    return newprograms;
  }

  template<unsigned int size, unsigned int cycles>
  std::string solve_part2_sensibly(const std::vector<Day16::move>& moves)
  {
    // instead of applying the moves every time, do it once, make a map of the transform
    // the spin and exchange moves are essentially value-preserving, so we can just make a map of those
    // then afterwards apply the swaps

    std::vector<move> spin_exchange_moves;
    std::vector<move> partner_moves;
    for (const auto& m : moves)
    {
      if (m.type==move::Spin || m.type==move::Exchange) spin_exchange_moves.push_back(m);
      else if (m.type==move::Partner) partner_moves.push_back(m);
    }

    // get a map of all the non-partner moves
    std::array<char, size> spin_exchange_moves_map;
    std::iota(spin_exchange_moves_map.begin(), spin_exchange_moves_map.end(), 0);
    dance(spin_exchange_moves, spin_exchange_moves_map);

    // get a pseudomap of the partner moves, and find it's period
    // if this takes very long, abort...
    std::array<char, size> partner_move_map;
    std::iota(partner_move_map.begin(), partner_move_map.end(), 'a');
    dance(partner_moves, partner_move_map);

    std::array<char, size> programs;
    std::iota(programs.begin(), programs.end(), 'a');
    programs = apply_partners(partner_move_map, programs);

    int period = 0;
    while(true)
    {
      assert(period < 100);
      period++;

      programs = apply_partners(partner_move_map, programs);
      if (programs == partner_move_map) break;
    }

    // reset the programs, do this thing for real
    std::iota(programs.begin(), programs.end(), 'a');

    // apply the spin/exchange moves by self-application of the map for each set-bit
    unsigned int num_dances = cycles;
    while(num_dances > 0)
    {
      if (num_dances & 1)
      {
        // if this bit is set, then apply the dance * 2**bit to the programs
        programs = apply_dances(spin_exchange_moves_map, programs);
      }

      // move the map forward one bit by applying it to itself
      spin_exchange_moves_map = apply_dances(spin_exchange_moves_map, spin_exchange_moves_map);
      num_dances = num_dances >> 1;
    }

    // apply the exchanges based on the period
    const unsigned int apply_count = cycles % period;
    for (unsigned int i = 0; i < apply_count; i++)
    {
      programs = apply_partners(partner_move_map, programs);
    }

    return std::string(programs.begin(), programs.end());
  }

}

#endif //AOC2017_DAY16_H
