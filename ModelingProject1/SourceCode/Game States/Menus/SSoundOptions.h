#pragma once

#include "GameState.h"

#include "GUIMenu.h"

#include <MainMenuSelection.h>
#include <MenuController.h>

class SSoundOptions : public GameState
{
  public:
   SSoundOptions( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   ~SSoundOptions();

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
   RPRGUI::GUIMenu* guiSoundMenu;
   Image::MainMenuSelection* soundMenu;
   boost::ptr_vector<Image::MenuController> controllers;
   Image::ArrowSoundMenu arrowImage;
   Image::CustomCursor customCursor;
   int numberOfPlayers;
};