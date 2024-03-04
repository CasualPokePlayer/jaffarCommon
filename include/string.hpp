#pragma once

/**
 * @file string.hpp
 * @brief Contains common functions related to manipulating strings
 */

#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>

namespace jaffarCommon
{

namespace string
{

// Function to split a string into a sub-strings delimited by a character
// Taken from stack overflow answer to https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
// By Evan Teran

template <typename Out>
__INLINE__ void split(const std::string &s, char delim, Out result)
{
  std::istringstream iss(s);
  std::string item;
  while (std::getline(iss, item, delim))
  {
    *result++ = item;
  }
}

__INLINE__ std::vector<std::string> split(const std::string &s, char delim)
{
 std::string newString = s;
 std::replace(newString.begin(), newString.end(), '\n', ' ');
 std::vector<std::string> elems;
 split(newString, delim, std::back_inserter(elems));
 return elems;
}

__INLINE__ std::string formatString (const char *format, ...)
{
  char *outstr = 0;
  va_list ap;
  va_start(ap, format);
  vasprintf(&outstr, format, ap);

  std::string outString = outstr;
  free(outstr);
  return outString;
}

} // namespace timing

} // namespace jaffarCommon
