#include "matfun.h"

int heaviside(int value, int threshold)
{
  if (value < threshold)
    return 0;
  return 1;
}

int sign(int value)
{
  if (value >= 0)
    return 1;
  return -1;
}
