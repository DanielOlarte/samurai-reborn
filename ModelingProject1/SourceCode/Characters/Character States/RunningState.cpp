
#include <algorithm>

#include "RunningState.h"

#include "PlayerSpriteStates.h"
#include <GameSound.h>
#include <PhysicModes.h>

GameCoreStates::RunningState::RunningState(int id, int characterID) : PlayerState( id, characterID )
{
}

GameCoreStates::RunningState::~RunningState(void)
{
}

int GameCoreStates::RunningState::checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, 
	                                 int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  GameCoreStates::ConditionsPlayerRunning isRunning = checkIfPlayerIsRunning(controller, keys);
  const int RETURNING_FROM_PREVIOUS_STATE = 1;

  if ( ( currentState == GameCoreStates::RUNNING || currentState == GameCoreStates::FAST_ATTACK ) &&
         isRunning.directionButtonPressed && isRunning.runningButtonPressed && 
         keyPreviouslyPressed != RETURNING_FROM_PREVIOUS_STATE  )
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( ( currentState == GameCoreStates::WALKING || currentState == GameCoreStates::STILL ||
       ( currentState == GameCoreStates::FAST_ATTACK && keyPreviouslyPressed == RETURNING_FROM_PREVIOUS_STATE ) ||
         previousState == GameCoreStates::JUMPING ) && 
         isRunning.directionButtonPressed && isRunning.runningButtonPressed )
  {
	GameSound::getInstance()->playSound(characterID, 0, 2);
    return GameCoreStates::CHANGE;
  }

  if ( currentState == GameCoreStates::FAST_ATTACK && previousState == GameCoreStates::JUMPING && 
       keyPreviouslyPressed != RETURNING_FROM_PREVIOUS_STATE)
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( keyPreviouslyPressed == GamePhysics::TO_WALKING || 
	  (!isRunning.directionButtonPressed && currentState == GameCoreStates::FAST_ATTACK) )
  {
	GameSound::getInstance()->playSound(characterID, 0, 2);
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}

int GameCoreStates::RunningState::checkChangeOfState(InputMapping::Controller& controller, std::list<InputMapping::Key> keys,
	                       int currentState, int previousState, GameCoreStates::PlayerState* newState, 
						   int keyPreviouslyPressed)
{
  return checkMovement(controller, keyPreviouslyPressed, previousState, currentState, keys);
}
