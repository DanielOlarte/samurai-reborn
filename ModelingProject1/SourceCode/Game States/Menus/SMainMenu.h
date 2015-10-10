#pragma once

#include "GameState.h"
#include "GUIMenu.h"
#include "MenuData.h"
#include "MenuStructs.h"

#include <MainMenuSelection.h>
#include <MenuController.h>

class SMainMenu : public GameState
{
  public:
   SMainMenu( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   ~SMainMenu();

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
   RPRGUI::GUIMenu* guiMainMenu;
   Image::MainMenuSelection* mainMenu;
   boost::ptr_vector<Image::MenuController> controllers;
   Image::ArrowMainMenu arrowImage;
   Image::CustomCursor customCursor;
   int numberOfPlayers;
};

