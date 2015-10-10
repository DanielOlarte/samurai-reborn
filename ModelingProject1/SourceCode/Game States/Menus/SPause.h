#pragma once

#include "GameState.h"
#include "GUIMenu.h"

#include <MainMenuSelection.h>
#include <MenuController.h>

class SPause : public GameState
{
  public:
   SPause( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   ~SPause();

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
   RPRGUI::GUIMenu* guiPauseMenu;
   Image::MainMenuSelection* pauseMenu;
   boost::ptr_vector<Image::MenuController> controllers;
   Image::ArrowPauseMenu arrowImage;
   Image::CustomCursor customCursor;
   int numberOfPlayers;
};