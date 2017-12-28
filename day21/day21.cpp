#include <cassert>
#include <algorithm>
#include <sstream>

#include "day21.h"
#include "../utils/aocutils.h"


Day21::pattern Day21::pattern::from_human_readable(unsigned int s, unsigned long long b)
{
  // invert the bits in b to be in the right format for storage and use by x,y
  pattern p={0};

  assert(s<=max_size);
  p.size = s;

  int i = (s*s)-1;
  for (int j=0; j<s*s; j++, i--)
  {
    p.bits[j] = bool(b & (1 << i));
  }

  return p;
}
unsigned long long Day21::pattern::to_human_readable() const
{
  unsigned long long b = 0;
  int i = (size*size)-1;
  for (int p=0; p<size*size; p++, i--)
  {
    b |= int(bits[p]) << i;
  }
  return b;
}

Day21::pattern Day21::pattern::flipped_x() const
{
  pattern p{0};
  p.size = size;
  for (int y=0;y<size;y++) for (int x=0;x<size;x++) p.bit(size - 1 - x,y) = bit(x,y);
  return p;
}
Day21::pattern Day21::pattern::flipped_y() const
{
  pattern p{0};
  p.size = size;
  for (int y=0;y<size;y++) for (int x=0;x<size;x++) p.bit(x, size - 1 - y) = bit(x,y);
  return p;
}

Day21::pattern Day21::pattern::rotate_ccw() const
{
  pattern p{0};
  p.size = size;
  for (int y=0;y<size;y++) for (int x=0;x<size;x++) p.bit(y,size - 1 - x) = bit(x,y);
  return p;
}

Day21::pattern Day21::pattern::rotate_cw() const
{
  pattern p{0};
  p.size = size;
  for (int y=0;y<size;y++) for (int x=0;x<size;x++) p.bit(size - 1 - y,x) = bit(x,y);
  return p;
}


Day21::pattern Day21::parse_pattern(const std::string& s)
{
  // slash-separated list of '.' for zero and '#' for one bits
  // examples: size 2 patterns, "../..", ".#/#."
  // examples: size 3 patterns, ".../.../...", "##./###/..."
  int size = 1 + std::count(s.begin(), s.end(), '/');
  assert(size<=pattern::max_size);   // we only expect size-2 to size-4 patterns
  assert(size>0);

  pattern p{(unsigned int)size, 0};
  auto iter = s.begin();
  for(int y=0;y<size;y++)
  {
    for (int x=0; x<size;x++,iter++)
    {
      assert(*iter=='#' || *iter=='.'); // expect only # or .
      if (*iter=='#') p.bit(x,y) = true;
    }

    // expect intermediate slashes, skip them
    if (y<size-1)
    {
      assert(*iter=='/');
      iter++;
    }
  }

  return p;
}

Day21::rule Day21::parse_rule(const std::string& s)
{
  // rules are a pair of patterns, separated by '=>'
  // example: "###/.../... => #.#./.#../.#../...."
  std::istringstream iss(s);
  std::string pattern1, pattern2;
  iss >> pattern1 >> AOCUtils::literal("=>") >> pattern2;
  assert(bool(iss));

  return {parse_pattern(pattern1), parse_pattern(pattern2)};
}

std::vector<Day21::rule> Day21::parse_rules(std::istream& stream)
{
  return AOCUtils::parseByLines<rule>(stream, parse_rule);
}

std::vector<Day21::rule> Day21::make_ruleset(const std::vector<rule>& base_rules)
{
  // for every rule in the base-rules, make a set of new rules for the rotations and flips
  // there are 8 orientations obtained by...
  // the original source pattern, and it's 3 other rotations
  // the (y-flip of the source pattern, and it's 3 other rotations  (or x-flip... either would do)
  std::vector<Day21::rule> ruleset;
  for (const auto& r : base_rules)
  {
    pattern source = r.source;
    ruleset.emplace_back(rule{source, r.target});
    ruleset.emplace_back(rule{source.rotate_cw(), r.target});
    ruleset.emplace_back(rule{source.rotate_ccw(), r.target});
    ruleset.emplace_back(rule{source.rotate_cw().rotate_cw(), r.target}); // lazy... rotate cw twice :)

    source = source.flipped_y();
    ruleset.emplace_back(rule{source, r.target});
    ruleset.emplace_back(rule{source.rotate_cw(), r.target});
    ruleset.emplace_back(rule{source.rotate_ccw(), r.target});
    ruleset.emplace_back(rule{source.rotate_cw().rotate_cw(), r.target}); // lazy... rotate cw twice :)
  }

  return ruleset;
}

bool match_pattern(const Day21::pattern& p, const std::function<bool(int, int)>& accessor)
{
  for (int y=0;y<p.size;y++)
  {
    for (int x=0;x<p.size;x++)
    {
      if (p.bit(x,y) != accessor(x,y)) return false;
    }
  }

  return true;
}

void copy_pattern(const Day21::pattern& p, const std::function<void(int, int, bool)>& writer)
{
  for (int y=0;y<p.size;y++)
  {
    for (int x=0;x<p.size;x++)
    {
      writer(x,y, p.bit(x,y));
    }
  }
}

std::pair<int, std::vector<char>> Day21::step(const std::vector<rule>& ruleset, const std::vector<char>& grid, int size)
{
  assert(grid.size() == size*size);

  // break the source grid up into units of 2 or 3... should always be divisible by one or t'other.
  const int block_size = (size & 1) ? 3 : 2;
  assert((size % block_size) == 0);

  const int num_blocks = size / block_size;

  // zero-initialise our output grid
  const int output_block_size = block_size + 1; // the output grid is made from each block, embiggened by 1 by the replacement rule
  const int output_size = output_block_size * num_blocks;
  std::vector<char> output_grid(output_size*output_size, 0);

  // for each block, try and match the rules in the ruleset
  for (int by = 0; by < num_blocks; by++)
  {
    const int dy = block_size * by;         // read ordinate in input grid
    const int ody = output_block_size * by; // write ordinate in outut grid

    for (int bx = 0; bx < num_blocks; bx++)
    {
      const int dx = block_size * bx;         // read ordinate in input grid
      const int odx = output_block_size * bx; // write ordinate in output grid

      bool didmatch = false;
      for (const auto& r : ruleset)
      {
        // check if this rule matches the input block
        if (r.source.size != block_size) continue;  // skip if this rule isn't valid for this block size
        if (match_pattern(r.source, [&grid, size, dx, dy](int x, int y) -> bool { return grid[(x+dx) + (y+dy)*size]; }))
        {
          didmatch = true;
          copy_pattern(r.target, [&output_grid, output_size, odx, ody](int x, int y, bool b) -> void { output_grid[(x+odx) + (y+ody)*output_size] = b; });
          break;
        }
      }

      assert(didmatch); // there should ALWAYS be a match?
    }
  }

  return {output_size, output_grid};
}

int Day21::solve_part1(const std::vector<rule>& rules, int iterations)
{
  // generate a ruleset from the rules...
  auto ruleset = make_ruleset(rules);

  // create the initial grid with the flyer in it
  std::vector<char> grid{0, 1, 0,
                         0, 0, 1,
                         1, 1, 1};

  // do some iterations... getting a bigger grid each time
  int size = 3;
  for (int i=0;i<iterations;i++)
  {
    auto result = step(ruleset, grid, size);
    size = result.first;
    grid = std::move(result.second);
  }

  // in the last grid, count the set values
  return std::count(grid.begin(), grid.end(), true);
}
