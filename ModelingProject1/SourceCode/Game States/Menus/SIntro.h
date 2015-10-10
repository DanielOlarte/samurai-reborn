#pragma once

#include "GameState.h"
#include <boost\ptr_container\ptr_vector.hpp>

class SIntro : public GameState
{
  public:
   SIntro( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   ~SIntro();

   void init();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();

  private:
   boost::ptr_vector<Image::GameImage> logos;
   int currentLogo;
};

