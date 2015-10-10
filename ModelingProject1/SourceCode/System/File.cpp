
#include <File.h>

std::string readLineFromFile(std::string sFilename, int row)
{
  std::string line;
  std::ifstream soundsFile ( sFilename, std::ifstream::in );
  
  if( !soundsFile.is_open() )
  {
    exit(1);
  }
  
  char n;
  int i = 0;

  while ( soundsFile.good() )
  {
    n = soundsFile.get();
    if(i == row)
	{
      line += n;
    }
    if(n == '\n')
	{
      i++;
    }
  }

  line.erase(line.size() - 1);
  soundsFile.close();
  return line;
}