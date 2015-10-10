#pragma once

#include "GameState.h"
#include "Level.h"
#include "AI.h"

#include <MenuSelection.h>

class SLevelOneJapan : public GameState
{
  public:
   SLevelOneJapan( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   ~SLevelOneJapan();

   void init();
   void resume();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();

   void initializePlayers();
   void initializeLevel();

   void handleChangeOfState(int idState);

  private:
   Level* japanLevel;
   AISystem::AI levelAI;
   Image::MenuSelection* inGameMenu;
};