#pragma once

#include <fstream>

class GameSaves
{
  public:
   GameSaves(void);
   ~GameSaves(void);

   void loadFileInformation();
   void saveFileInformation();

  private:
   FILE* saveFile;
};

