//
// Created by wuggy on 20/12/2017.
//

#ifndef AOC2017_DAY11_H
#define AOC2017_DAY11_H

#include <cassert>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>

namespace Day11
{

  struct hexpos
  {
    // hex ordinates work on a plane-restricted 3d-ordinate system
    // see: https://www.redblobgames.com/grids/hexagons/

    int x;
    int y;
    int z;

    inline void check()
    {
      // hex ordinates have the constraint that x + y + z = 0;
      assert( x + y + z == 0);
    }

    // (manhattan) distance of this point (from origin)
    inline int dist()
    {
      return (std::abs(x) + std::abs(y) + std::abs(z)) >> 1;
    }
  };

  inline hexpos operator+(const hexpos& a, const hexpos& b)
  {
    hexpos result{a.x + b.x, a.y + b.y, a.z + b.z};
    result.check();
    return result;
  }

  inline hexpos operator-(const hexpos& a, const hexpos& b)
  {
    hexpos result{a.x - b.x, a.y - b.y, a.z - b.z};
    result.check();
    return result;
  }

  inline hexpos& operator+=(hexpos& a, const hexpos& b)
  {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.check();
    return a;
  }

  inline hexpos& operator-=(hexpos& a, const hexpos& b)
  {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.check();
    return a;
  }

  namespace directions
  {
    // constants for hex directions
    constexpr hexpos n{0, 1, -1};
    constexpr hexpos s{0, -1, 1};

    constexpr hexpos ne{1, 0, -1};
    constexpr hexpos sw{-1, 0, 1};

    constexpr hexpos nw{-1, 1, 0};
    constexpr hexpos se{1, -1, 0};

    hexpos from_string(const std::string& str);
  }

  std::vector<std::string> parse_stream(std::istream& stream);
  std::vector<std::string> parse_string(const std::string& str);
  std::pair<int, int> solve(const std::vector<std::string>& moves);
} // namespace Day11

#endif //AOC2017_DAY11_H
