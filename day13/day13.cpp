//
// Created by wuggy on 22/12/2017.
//

#include <cassert>
#include <algorithm>
#include <array>

#include "day13.h"
#include "../utils/aocutils.h"




void Day13::sentry::reset()
{
  sentry_pos = 0;
  sentry_dir = 1;
}

void Day13::sentry::next_tick()
{
  // move the sentry to the next position
  // if that would over/under-flow, invert the orientation and do it again
  int newpos = sentry_pos + sentry_dir;
  if (newpos<0 || newpos>=range)
  {
    sentry_dir *= -1;
    newpos = sentry_pos + sentry_dir;
  }
  assert(newpos>=0);
  assert(newpos<range);

  sentry_pos = newpos;
}

void Day13::state::init(const std::vector<sentry> &sentries)
{
  max_depth = -1;
  for (const Day13::sentry &sentry : sentries)
  {
    firewall[sentry.depth] = sentry;
    max_depth = std::max(max_depth, sentry.depth);
  }
}

bool Day13::state::next_tick()
{
  // ordering is important: out packet moves FIRST, then sentries move AFTER
  // move time and our packet forward
  tick++;
  packet_depth++;

  // if our packet depth matches a sentry at the zeroth position, then we've been detected
  bool detected = false;
  try
  {
    detected = (firewall.at(packet_depth).sentry_pos == 0);
  }
  catch(std::out_of_range& x)
  {
    // ignore... just means there's no sentry on the firewall depth that out packet is on
  }

  // move all our sentries forward one position
  for (auto& pr : firewall) pr.second.next_tick();

  return detected;
}

void Day13::state::reset()
{
  tick = -1;
  packet_depth = -1;
  for (auto& pr : firewall) pr.second.reset();
}

std::vector<Day13::sentry> Day13::parse_sentries(std::istream& stream)
{
  return AOCUtils::parseByLines<sentry>(stream,
                                        [](const std::string& s) -> sentry
                                        {
                                          std::istringstream iss(s);
                                          int layer = -1, depth = -1;
                                          iss >> layer >> AOCUtils::literal(":") >> depth;
                                          assert(iss);
                                          return sentry(layer, depth);
                                        });
}


namespace
{
  std::pair<bool, int> run_simulation(Day13::state& state, bool stop_on_detected = false)
  {
    // run the state until our pos is past the end
    int trip_severity = 0;
    bool was_detected = false;
    while (state.packet_depth < state.max_depth)
    {
      bool detected = state.next_tick();
      if (detected)
      {
        was_detected = true;  // we were detected at least once

        const int severity = state.packet_depth * state.firewall.at(state.packet_depth).range;
        trip_severity += severity;

        if (stop_on_detected) break;
      }
    }

    return std::make_pair(was_detected, trip_severity);
  }
} // anonymous namespace

int Day13::solve_part1(const std::vector<sentry> &sentries)
{
  Day13::state state;
  state.init(sentries);
  return run_simulation(state).second;
}

int Day13::solve_part2(const std::vector<sentry> &sentries)
{
  // keep running the simulation with a larger delay until we find one that succeeds
  Day13::state state;
  state.init(sentries);

  int delay = 0;
  while(true)
  {
    state.packet_depth -= delay;
    bool detected = run_simulation(state, true).first;
    if (!detected) break; // found a successful way through the firewall

    delay++;
    state.reset();

    if ((delay % 1000) == 0) std::cout << delay << std::endl;
  }

  return delay;
}

long Day13::solve_part2_sensibly(const std::vector<sentry>& sentries)
{
  // instead of brute-forcing, work through the periods
  // period = 2 * (range - 1)
  // we want to find a delay such that all sentries are 'off-period' when the packet reaches them
  // for a delay 'd', this reaches 'sentry.depth' after 'd + sentry.depth' ticks
  // a delay 'd' is bad if '(d + sentry.depth) % period == 0'

  // sort sentries by their period (noddy improvement on performance)
  std::vector<sentry> sorted_sentries = sentries;
  std::sort(sorted_sentries.begin(), sorted_sentries.end(), [](const sentry& a, const sentry& b) -> bool {return a.range < b.range; });

  for (int delay = 0; true; delay++)
  {
    bool bad = false;
    for (const sentry& s : sorted_sentries)
    {
      const int period = 2 * (s.range - 1);
      bad = (((delay + s.depth) % period) == 0);
      if (bad) break;
    }
    if (!bad) return delay;
  }
}
