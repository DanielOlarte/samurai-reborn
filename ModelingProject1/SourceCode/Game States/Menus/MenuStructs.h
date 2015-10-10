#pragma once

#include "GameImage.h"

namespace Image
{
  struct ArrowMenu
  {
    GameImage* arrow;
    int optionSelected;

	virtual void updatePositionArrow() { };
  };

  struct ArrowMainMenu : ArrowMenu
  {
	void updatePositionArrow();
  };

  struct ArrowPauseMenu : ArrowMenu
  {
    void updatePositionArrow();
  };

  struct ArrowSoundMenu : ArrowMenu
  {
    void updatePositionArrow();
  };
}

namespace Image
{
  struct PlayersInitialize
  {
	int characterID;
	int controllerID;
  };

  struct MenuEndData
  {
    int loserMode;

	MenuEndData(int loser) { loserMode = loser; }
	MenuEndData(){};
  };

  struct CustomCursor
  {
    GameImage* cursor;
  };
}
