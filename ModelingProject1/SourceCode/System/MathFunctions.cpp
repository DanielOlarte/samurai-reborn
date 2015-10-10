
#include "MathFunctions.h"
#include <MathConstants.h>

#include <math.h>

int nextPowerOfTwo(int value)
{
  double logbase2 = log( double(value) ) / log( double(2) );
  return round( pow( 2, ceil(logbase2) ) );
}

int round(double value)
{
  return (int)(value + 0.5);
}

bool comparatorValuesInt(int sign, int left, int right)
{
  if ( sign == Math::LESS_OR_EQUAL )
  {
	return left <= right;
  }
  else if ( sign == Math::GREATER_OR_EQUAL )
  {
	return left >= right;
  }
  else if ( sign == Math::LESS_THAN )
  {
	return left < right;
  }
  else if ( sign == Math::GREATER_THAN )
  {
	return left > right;
  }

  return false;
}
