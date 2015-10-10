#pragma once

#include "GameState.h"

#include <MainMenuSelection.h>
#include <MenuController.h>

class SCredits : public GameState
{
  public:
   SCredits( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   ~SCredits();

   void init();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();

   void createGUI();

   static void inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                         std::list<InputMapping::Key> keys, Image::MenuSelection& menu);

  private:
   Image::GameImage* background;
   Image::MainMenuSelection* menuCredits;
   boost::ptr_vector<Image::MenuController> controllers;
   int numberOfPlayers;
};