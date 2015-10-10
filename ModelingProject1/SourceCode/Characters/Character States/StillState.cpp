
#include "StillState.h"

GameCoreStates::StillState::StillState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::StillState::~StillState(void)
{
}

int GameCoreStates::StillState::checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, 
	                                 int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  return GameCoreStates::CHANGE;
}