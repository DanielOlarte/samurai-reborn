#pragma once

#include "GameState.h"

#include "Level.h"

#include <MenuSelection.h>

class Deathmatch : public GameState
{
  public:
   Deathmatch( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   ~Deathmatch();

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
   Level* deathmatchLevel;
   Image::MenuSelection* inGameMenu;
};