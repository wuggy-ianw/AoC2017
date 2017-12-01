//
// Created by wuggy on 01/12/2017.
//

#include <iostream>

#include "day01.h"


std::size_t solve(const std::string& captcha, std::string::const_iterator shifted_iter)
{
  // add the integer value of an matching pair of characters
  std::size_t sum = 0;
  for (auto i = captcha.begin(); i != captcha.end(); i++, shifted_iter++)
  {
    // if our shifted iter has fallen off the end, start it from the beginning
    if (shifted_iter == captcha.end()) shifted_iter = captcha.begin();

    // if our current and shifted characters match, this value should be added
    if (*i == *shifted_iter) sum += (*i - '0');
  }

  return sum;
}


std::size_t Day1::solve_part1(const std::string& captcha)
{
  return solve(captcha, captcha.begin()+1);
}

std::size_t Day1::solve_part2(const std::string& captcha)
{
  return solve(captcha, captcha.begin() + (captcha.length() / 2));
}
