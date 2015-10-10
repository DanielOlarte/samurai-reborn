
#include <algorithm>

#include "WalkingState.h"

GameCoreStates::WalkingState::WalkingState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::WalkingState::~WalkingState(void)
{
}

int GameCoreStates::WalkingState::checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, 
	                                 int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  const int RETURNING_FROM_PREVIOUS_STATE = 1;
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(controller, keys);

  if ( currentState == GameCoreStates::FAST_ATTACK && isPacing.directionButtonPressed &&
      keyPreviouslyPressed != RETURNING_FROM_PREVIOUS_STATE)
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( currentState != GameCoreStates::STILL &&
      keyPreviouslyPressed != InputMapping::RAW_INPUT_NO_BUTTON &&
      keyPreviouslyPressed != RETURNING_FROM_PREVIOUS_STATE &&
      ( isPacing.runningButtonPressed ) )
  {
    return GameCoreStates::NO_CHANGE;
  }

  return GameCoreStates::CHANGE;
}
