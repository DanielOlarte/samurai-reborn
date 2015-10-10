#pragma once

#include "GameState.h"
#include "GUIMenu.h"
#include "MenuData.h"
#include "MenuStructs.h"

#include <MainMenuSelection.h>
#include <MenuController.h>

class SArenaWinner : public GameState
{
  public:
   SArenaWinner( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   ~SArenaWinner();

   void init();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();

   void createGUI( );

   void handleMouseUp(Uint8 button, Vector2f mousePosition);

   static void inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                         std::list<InputMapping::Key> keys, Image::MenuSelection& menu);

  private:
   RPRGUI::GUIMenu* guiArenaWinnerMenu;
   Image::MainMenuSelection* arenaWinnerMenu;
   boost::ptr_vector<Image::MenuController> controllers;
   int numberOfPlayers;
};