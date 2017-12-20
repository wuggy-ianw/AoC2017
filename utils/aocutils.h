//
// Created by wuggy on 02/12/2017.
//

#ifndef AOC2017_AOCUTILS_H
#define AOC2017_AOCUTILS_H

#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

namespace AOCUtils
{
  // read lines from the file, and parse them with the function, collect them into a vector
  template<typename T>
  std::vector< T > parseByLines(std::istream& stream, const std::function<T(const std::string&)>& lineParser )
  {
    std::vector<T> lines;
    for(std::string line; std::getline(stream, line); )
    {
      if (line.length()==0) continue; // skip blank lines
      lines.push_back(lineParser(line));
    }

    return lines;
  }

  // parse a line into typed items using a stringstream
  template<typename T>
  std::vector< T > parseItem(const std::string& item)
  {
    std::vector< T > values;
    std::istringstream ss(item);
    for (T val; ss >> val;)
    {
      values.push_back(val);
    }

    return values;
  }

  // parse a comma-separated line into typed items
  template<typename T>
  std::vector< T > parseCommaSeparatedItems(const std::string& line, const std::function<T(const std::string&)>& itemParser )
  {
    std::vector< T > values;
    std::istringstream ss(line);
    for (std::string s; std::getline(ss, s, ',');)
    {
      values.push_back(itemParser(s));
    }

    return values;
  }


  // match a literal string (or fail very badly)
  struct literal
  {
    explicit literal(const std::string& s) : s(s) {}
    explicit literal(std::string&& s) : s(std::move(s)) {}
    std::string s;
  };

  std::istream& operator>> (std::istream& s, const literal& l);


} // namespace AOCUtils

#endif //AOC2017_AOCUTILS_H
