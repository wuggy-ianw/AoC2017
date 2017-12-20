//
// Created by wuggy on 20/12/2017.
//

#include "day11.h"
#include "../utils/aocutils.h"

#include <sstream>


Day11::hexpos Day11::directions::from_string(const std::string &str)
{
  static std::map<std::string, hexpos> dirs{
      std::make_pair("n", n),
      std::make_pair("s", s),
      std::make_pair("ne", ne),
      std::make_pair("sw", sw),
      std::make_pair("nw", nw),
      std::make_pair("se", se)
  };

  return dirs[str];
}


std::vector<std::string> Day11::parse_stream(std::istream &stream)
{
  std::vector<std::vector<std::string>> parsed = AOCUtils::parseByLines<std::vector<std::string>>(stream,
                                                                                                  [](const std::string& s) -> std::vector<std::string>{
                                                                                                    return AOCUtils::parseCommaSeparatedItems<std::string>(s, [](const std::string& s) -> std::string {return s;});
                                                                                                  });
  assert(parsed.size()==1);
  return parsed[0];
}

std::vector<std::string> Day11::parse_string(const std::string& str)
{
  std::istringstream iss(str);
  return parse_stream(iss);
}


std::pair<int, int> Day11::solve(const std::vector<std::string>& moves)
{
  // move position based on the moves list
  hexpos p{0};
  int maxdistance = 0;
  for(const std::string& mov : moves)
  {
    p += directions::from_string(mov);
    maxdistance = std::max(maxdistance, p.dist());
  }

  // return the manhattan distance
  return std::make_pair(p.dist(), maxdistance);
}
