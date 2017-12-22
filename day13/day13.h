//
// Created by wuggy on 22/12/2017.
//

#ifndef AOC2017_DAY13_H
#define AOC2017_DAY13_H


#include <vector>
#include <map>

namespace Day13
{

  struct sentry
  {
    int depth;  // depth of layer
    int range;
    int sentry_pos;
    int sentry_dir;


    sentry() : depth(-1), range(0), sentry_pos(0), sentry_dir(0) {}
    sentry(int d, int r, int sp=0, int sd=1) : depth(d), range(r), sentry_pos(sp), sentry_dir(sd) {}

    sentry(const sentry& s) = default;
    sentry(sentry&& s) = default;

    sentry& operator=(const sentry& other) = default;

    inline bool operator==(const sentry& other) const
    {
      return (depth == other.depth) && (range == other.range) && (sentry_pos == other.sentry_pos) && (sentry_dir == other.sentry_dir);
    }

    void reset();
    void next_tick();
  };

  struct state
  {
    int tick = -1;          // one tick before tick-zero
    int packet_depth = -1;  // one layer before the zeroth layer

    int max_depth = -1;
    std::map<int, sentry> firewall;

    void init(const std::vector<sentry> &sentries);

    // returns true of moving to the new position on this tick moved onto layer where a sentry caught it
    bool next_tick();

    void reset();
  };

  std::vector<sentry> parse_sentries(std::istream& stream);
  int solve_part1(const std::vector<sentry>& sentries);
  int solve_part2(const std::vector<sentry>& sentries);
  long solve_part2_sensibly(const std::vector<sentry>& sentries);
}

#endif //AOC2017_DAY13_H
