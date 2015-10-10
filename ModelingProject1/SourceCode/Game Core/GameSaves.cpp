
#include "GameSaves.h"

GameSaves::GameSaves(void)
{
  saveFile = NULL;
}

GameSaves::~GameSaves(void)
{
  delete saveFile;
}
