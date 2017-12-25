#include <cassert>

#include "day16.h"
#include "../utils/aocutils.h"



Day16::move Day16::parse_move(const std::string& str)
{
  std::istringstream stream(str);
  move m;

  char c;
  stream >> c;
  assert(bool(stream));

  if (c=='s')
  {
    m.type=move::Spin;
    stream >> m.spin_size;
    assert(bool(stream));
  }
  else if (c=='x')
  {
    m.type=move::Exchange;
    stream >> m.swap_pos1 >> AOCUtils::literal("/") >> m.swap_pos2;
    assert(bool(stream));
  }
  else if (c=='p')
  {
    m.type=move::Partner;
    stream >> m.swap_program1 >> AOCUtils::literal("/") >> m.swap_program2;
    assert(bool(stream));
  }
  else assert(false); // unknown type of move

  return m;
}

std::vector<Day16::move> Day16::parse_moves(std::istream& stream)
{
  std::vector<std::string> lines=AOCUtils::parseByLines<std::string>(stream,[](const std::string& s)->std::string{return s;});
  assert(lines.size()==1);

  return AOCUtils::parseCommaSeparatedItemsFromString<move>(lines[0], parse_move);
}

