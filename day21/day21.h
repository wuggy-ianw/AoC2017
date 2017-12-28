#ifndef AOC2017_DAY21_H
#define AOC2017_DAY21_H

#include <istream>
#include <vector>
#include <array>
#include <cassert>

namespace Day21
{

  struct pattern
  {
    static constexpr int max_size = 4;
    typedef std::array<bool, max_size*max_size> bitset; // instead of using bitset, just use a fat-array

    unsigned int size;
    bitset bits;

    inline bool& bit(int x, int y)       { assert(x<size); assert(y<size); return bits[x + y*size]; }
    inline bool  bit(int x, int y) const { assert(x<size); assert(y<size); return bits[x + y*size]; }

    bool operator==(const pattern& p) const { return size == p.size && bits == p.bits; }
    bool operator!=(const pattern& p) const { return size != p.size || bits != p.bits; }

    bool operator> (const pattern& p)  const { return (size >  p.size) || (bits >  p.bits); }

    static pattern from_human_readable(unsigned int s, unsigned long long b);
    unsigned long long to_human_readable() const;

    pattern flipped_x() const;
    pattern flipped_y() const;

    pattern rotate_ccw() const;
    pattern rotate_cw() const;
  };

  struct rule
  {
    pattern source;
    pattern target;
  };

  pattern parse_pattern(const std::string& s);
  rule parse_rule(const std::string& s);

  std::vector<rule> parse_rules(std::istream& stream);
  std::vector<rule> make_ruleset(const std::vector<rule>& base_rules);

  std::pair<int, std::vector<char>> step(const std::vector<rule>& ruleset, const std::vector<char>& grid, int size);

  int solve_part1(const std::vector<rule>& rules, int iterations = 5);
}

#endif //AOC2017_DAY21_H
