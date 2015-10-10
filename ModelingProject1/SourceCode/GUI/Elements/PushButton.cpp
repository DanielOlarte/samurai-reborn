#include "PushButton.h"

#include "GameState.h"

RPRGUI::PushButton::PushButton(int id, Vector2f pos, Vector2f dim, Vector2f textPos)
{
  this->id = id;
  position = pos;
  dimensions = dim;
  texturePosition = textPos;
}

RPRGUI::PushButton::~PushButton(void)
{
}

int RPRGUI::PushButton::eventClicked(bool* isRunning, int* gameMode)
{
  if ( (MainStates::GameStates)idChangeState == MainStates::STATE_EXIT )
  {
    *isRunning = false;
  }
  
  *gameMode = idGameMode;
  return idChangeState;
}
