#pragma once

#include <boost/ptr_container/ptr_vector.hpp>
#include "PushButton.h"
#include "ImageObject.h"
#include "GameSound.h"

namespace Image
{
  class MenuSelection
  {
    public:
	 MenuSelection() { };
	 ~MenuSelection();

	 virtual Image::ImageObject& getController();

	 virtual void moveSelection(int direction) { };

	 int getCurrentPlayers() { return numberOfPlayers; }
	 void setNumberOfPlayers(int number) { numberOfPlayers = number; }

	 bool isPlayerOneSelected() { return playerOneSelected; }
	 void setPlayerOneSelected(bool selected) { playerOneSelected = selected; }

	 bool isPlayerTwoSelected() { return playerTwoSelected; }
	 void setPlayerTwoSelected(bool selected) { playerTwoSelected = selected; }
     
	 int getCurrentSelection() { return currentSelection; }
	 void setCurrentSelection(int selection) { currentSelection = selection; }

	 int getNewIdGameState() { return idNewGameState; }
	 void setNewIdGameState(int id) { idNewGameState = id; }

	 boost::ptr_vector<RPRGUI::PushButton>& getListButtons() { return listButtons; }
	 void setListButtons(boost::ptr_vector<RPRGUI::PushButton>* list) { listButtons = *list; }

	 bool getIsRunning() { return isRunning; }
	 void setIsRunning(bool running) { isRunning = running; }
	    
	 int getCurrentGameMode() { return currentGameMode; }
     void setCurrentGameMode(int mode) { currentGameMode = mode; }

    protected:
	 boost::ptr_vector<RPRGUI::PushButton> listButtons;
     boost::ptr_vector<Image::ImageObject> listStaticImages;
	 int currentSelection;
     int idNewGameState;
	 int numberOfPlayers;
	 bool playerOneSelected, playerTwoSelected;
	 bool isRunning;
	 int currentGameMode;
  };
}