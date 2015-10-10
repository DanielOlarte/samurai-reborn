#pragma once

#include <string>
#include <sstream>

template <typename DataType>
std::string parseDataToString(DataType data)
{
  std::string outData;
  std::stringstream out;

  out.str(std::string());
  out << data;

  outData = out.str();

  return outData;
}

template <typename DataType>
int parseStringToInt(DataType data)
{
  int newInteger = 0;
  newInteger = atoi(&data);

  return newInteger;
}

template <typename DataType>
int parsePointerStringToInt(DataType data)
{
  int newInteger = 0;
  newInteger = atoi(data);

  return newInteger;
}