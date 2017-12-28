#ifndef AOC2017_DAY22_H
#define AOC2017_DAY22_H

#include <limits>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>


namespace Day22
{
  typedef int ordinate;
  static constexpr ordinate ordinate_max = std::numeric_limits<ordinate>::max();
  static constexpr ordinate ordinate_min = std::numeric_limits<ordinate>::min();

  struct ordinate_pair_hash {
    inline std::size_t operator()(const std::pair<ordinate,ordinate> &p) const {
      return std::size_t(p.first)*std::size_t(7901) + std::size_t(p.second);  // 7901 is a nice-ish prime
    }
  };


  struct sparse_grid
  {
    std::unordered_map<std::pair<ordinate, ordinate>, char, ordinate_pair_hash> grid;   // grid is empty, except when an ordinate is 'in' the set

    char at(ordinate x, ordinate y) const;
    void set(ordinate x, ordinate y, char c);
  };

  struct ant
  {
    ordinate x;
    ordinate y;

    enum direction_t
    {
      Up,
      Down,
      Left,
      Right
    } direction;

    ant() : x(0), y(0), direction(Up) {}
    ant(ordinate x, ordinate y, direction_t d) : x(x), y(y), direction(d) {}

    void move();
    void switch_direction(char state);
  };

  // returns true if we infected a location on this step
  bool step(sparse_grid& grid, ant& ant, const std::function<char(char)>& change_state);

  std::pair<ordinate, ordinate> populate_grid(sparse_grid& grid, const std::vector<std::string>& input);

  unsigned int solve(const sparse_grid& initial_grid, int start_x, int start_y, int iterations, const std::function<char(char)>& change_state);

  char solve_part1_change_state(char c);
  char solve_part2_change_state(char c);

  unsigned int solve_part1(const sparse_grid& initial_grid, int start_x, int start_y, int iterations);
  unsigned int solve_part2(const sparse_grid& initial_grid, int start_x, int start_y, int iterations);
}

#endif //AOC2017_DAY22_H
