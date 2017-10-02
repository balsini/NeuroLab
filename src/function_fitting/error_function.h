#ifndef ERROR_FUNCTION_H
#define ERROR_FUNCTION_H

#include <vector>
#include <cmath>
#include <limits>


template<class T>
long double error_least_square(const std::vector<std::pair<T, T> > &s)
{
  long double c = 0;

  for (const auto &e : s)
    c += pow(e.first - e.second, 2);

  return sqrt(c);
}


template<class T>
long double error_least_square_relative(const std::vector<std::pair<T, T> > &s)
{
  long double c = 0;

  for (const auto &e : s)
    c += pow((e.first - e.second) / e.second, 2);

  return sqrt(c);
}


template<class T>
long double error_max_relative(const std::vector<std::pair<T, T> > &s)
{
  long double max = std::numeric_limits<long double>::min();
  long double value;

  for (const auto &e : s) {
    value = abs(e.first - e.second);

    if (value > max)
      max = value;
  }

  return max;
}

#endif
