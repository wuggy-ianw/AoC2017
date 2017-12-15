//
// Created by wuggy on 02/12/2017.
//

#include "aocutils.h"

std::istream& AOCUtils::operator>>(std::istream &s, const AOCUtils::literal &l)
{
  for (char literal_char : l.s)
  {
    char c;
    s >> c;
    if (c != literal_char)
    {
      // mark fail on the stream if we got a non-matching character
      s.putback(c);
      s.setstate(std::ios_base::failbit);
      break;
    }
  }
  return s;
}
