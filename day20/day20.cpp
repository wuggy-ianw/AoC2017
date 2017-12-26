#include <cassert>
#include <limits>
#include <list>
#include <algorithm>

#include "day20.h"
#include "../utils/aocutils.h"

Day20::particle Day20::parse_particle(const std::string& str)
{
  // example: "p=<7688,-2445,1026>, v=<-55,66,-142>, a=<-8,0,6>"
  particle p;
  auto comma = AOCUtils::literal(",");
  std::istringstream stream(str);

  stream >> AOCUtils::literal("p=<") >> p.p.x >> comma >> p.p.y >> comma >> p.p.z >> AOCUtils::literal(">,");
  stream >> AOCUtils::literal("v=<") >> p.v.x >> comma >> p.v.y >> comma >> p.v.z >> AOCUtils::literal(">,");
  stream >> AOCUtils::literal("a=<") >> p.a.x >> comma >> p.a.y >> comma >> p.a.z >> AOCUtils::literal(">");
  assert(stream);

  return p;
}

Day20::vec3 Day20::project_to_time(const particle& p, time_ticks t)
{
  // the kinematics equation is high-school maths. :)
  // p' = p + v*t + (a * t**2 )/2
  // however! the tick-ordering applies ONE MORE acceleration-step to velocity
  // since the ordering adjusts velocity BEFORE updating position
  // so we need a sly t+1 instead of t (and a bit of head scratching to get the maths right)
  return p.p + (p.v * t) + (p.a * (t+1)*t)/2.0;
}


std::size_t Day20::solve_part1(const std::vector<particle>& particles)
{
  // project all the particles forward in time quite a bit, pick the one with the lowest manhatten distance
  const time_ticks far_future = 1000;
  value_type smallest_distance = std::numeric_limits<value_type>::max();
  size_t smallest_index = 0;
  for (size_t i=0;i<particles.size();i++)
  {
    value_type dist = project_to_time(particles[i], far_future).dist();
    if (dist < smallest_distance)
    {
      smallest_distance = dist;
      smallest_index = i;
    }
  }

  return smallest_index;
}


std::pair<Day20::time_ticks, Day20::value_type> search_for_collision(const Day20::particle& a, const Day20::particle& b)
{
  // the distance function is in the long time concave... start far away, use a small-ish step size
  Day20::time_ticks t = 200;   // start somewhere non-zero, somewhat into the future
  Day20::time_ticks step = 16; // with a 'bigish' step size, power of 2 for simplicity

  Day20::value_type dist_t = 0; // keep the minimum for debugging porpoises
  while( t>=0 && step)
  {
    dist_t = (Day20::project_to_time(a, t) - Day20::project_to_time(b, t)).dist();
    if (dist_t < 1) // floating point approximation
    {
      // this is an actual collision at time t
      return {t, dist_t};
    }

    auto dist_t_plus_step = (Day20::project_to_time(a, t+step) - Day20::project_to_time(b, t+step)).dist();
    auto dist_t_sub_step = (t-step >= 0)? (Day20::project_to_time(a, t-step) - Day20::project_to_time(b, t-step)).dist() : std::numeric_limits<Day20::value_type>::max();

    // if our old value is better than either step adjustment
    if (dist_t < dist_t_plus_step && dist_t < dist_t_sub_step)
    {
      // step size is too big, shrink it, try again
      step = step >> 1;
      continue;
    }

    // otherwise, plus or sub one step is better than our current t, use that instead
    if (dist_t_plus_step < dist_t)
    {
      t = t + step;
      continue;
    }

    if (dist_t_sub_step <= dist_t)  // <= so we favour the earliest value with this distance
    {
      t = t - step;
      continue;
    }

    // if we reach here, we must not have collided, but we might be stick at a minima plateu where
    // several time values have the same distance...
    // just pick a lower step size so we have finite runtime and pray...
    step = step >> 1;
  }

  // we never reached a collision
  return {-1, dist_t};
}


int Day20::solve_part2(const std::vector<particle>& particles)
{
  // rather than doing complicated collision solving, run the simulation
  // when the delta_distance between two particles has increased between two iterations
  // then the distance between these particles will only always increase (i.e. they never
  // can collide).

  // collect all the collisions
  struct collision
  {
    time_ticks time;

    size_t particle_i;
    size_t particle_j;
  };
  std::vector<collision> collisions;

  // for each pair, find the time they MIGHT collide (if any)
  for(size_t i=0;i<particles.size();i++)
  {
    for(size_t j=i+1;j<particles.size();j++)
    {
      auto search_result = search_for_collision(particles[i], particles[j]);
      if (search_result.first>=0)
      {
        collisions.emplace_back(collision{search_result.first, i, j});
      }
    }
  }

  // sort the collisions by the time they occur
  std::sort(collisions.begin(), collisions.end(), [](const collision& a, const collision& b) -> bool {return a.time < b.time; });

  // work out the time at which particles collided (i.e. when they were alive until)
  // go through the collisions in order and apply them
  // a collision with an already dead particle is ignored
  std::vector<time_ticks> particle_died_at(particles.size(), std::numeric_limits<time_ticks>::max());
  for (const auto& c : collisions)
  {
    // if either particle is already dead, skip
    if (particle_died_at[c.particle_i]<c.time || particle_died_at[c.particle_j]<c.time) continue;

    // mark these particles as dead at this time
    // this may happen multiple times to the same value for n-way collisions
    particle_died_at[c.particle_i] = c.time;
    particle_died_at[c.particle_j] = c.time;
  }

  // count the number of particles that didn't die!
  return std::count_if(particle_died_at.begin(), particle_died_at.end(), [](time_ticks t)->bool {return t == std::numeric_limits<time_ticks>::max(); });
}
