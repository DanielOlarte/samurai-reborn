#pragma once

#include <string>
#include <fstream>

template <typename DataTypeOutput>
DataTypeOutput readDataTypeFromFile(std::ifstream& stream)
{
  DataTypeOutput dataOutput;

  if( !(stream >> dataOutput) )
  {
    throw std::exception("Failed To Read A Data Value From A File.");
  }

  return dataOutput;
}

std::string readLineFromFile(std::string filename, int row);