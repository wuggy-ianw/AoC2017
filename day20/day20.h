#ifndef AOC2017_DAY20_H
#define AOC2017_DAY20_H

#include <vector>
#include <istream>
#include <cmath>

namespace Day20
{

  typedef long long time_ticks;
  typedef long long value_type;

  struct vec3
  {
    value_type x=0, y=0, z=0;

    vec3() = default;
    vec3(value_type x, value_type y, value_type z) : x(x), y(y), z(z) {}

    // copiable, copy-assignable, movable, move-assignable
    vec3(const vec3&) = default;
    vec3& operator=(const vec3&) = default;
    vec3(vec3&&) = default;
    vec3& operator=(vec3&&) = default;

    inline value_type dist() const
    {
      // manhattan distance
      return std::abs(x) + std::abs(y) + std::abs(z);
    }

    inline vec3 operator+(const vec3& v) const      { return {x + v.x, y + v.y, z + v.z}; }
    inline vec3 operator-(const vec3& v) const      { return {x - v.x, y - v.y, z - v.z}; }
    inline vec3 operator*(const value_type s) const { return {x*s, y*s, z*s}; }
    inline vec3 operator/(const value_type s) const { return {x/s, y/s, z/s}; }

    inline vec3& operator+=(const vec3& v)          { x += v.x; y += v.y; z += v.z; return *this; }

    inline bool operator==(const vec3& v) const { return x==v.x && y==v.y && z==v.z; }
    inline bool operator!=(const vec3& v) const { return x!=v.x || y!=v.y || z!=v.z; }
  };

  struct particle
  {
    vec3 p; // position at t==0
    vec3 v; // velocity at t==0
    vec3 a; // acceleration at t==0

    particle() = default;
    particle(const particle&) = default;
    particle(particle&&) = default;
  };

  particle parse_particle(const std::string& str);

  vec3 project_to_time(const particle& p, time_ticks t);

  std::size_t solve_part1(const std::vector<particle>& particles);
  int solve_part2(const std::vector<particle>& particles);
}

#endif //AOC2017_DAY20_H
