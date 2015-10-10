
#include <algorithm>
#include "PlayerState.h"
#include <SpriteDataConstants.h>

GameCoreStates::PlayerState::PlayerState(int id) : State(id)
{
}

GameCoreStates::PlayerState::PlayerState(int id, int characterID)
{
  currentID = id;
  this->characterID = characterID;
}

int GameCoreStates::PlayerState::checkIfEqualStates(InputMapping::Controller& controller, std::list<InputMapping::Key> keys, 
	                             int currentState, int previousState, GameCoreStates::PlayerState* newState,
                                 int keyPreviouslyPressed)
{
  return checkChangeOfState(controller, keys, currentState, previousState, newState, keyPreviouslyPressed);
}

int GameCoreStates::PlayerState::checkChangeOfState(InputMapping::Controller& controller, std::list<InputMapping::Key> keys, 
	                             int currentState, int previousState, GameCoreStates::PlayerState* newState,
                                 int keyPreviouslyPressed)
{
  if ( currentState == newState->getCurrentID() )
  {
    return GameCoreStates::NO_CHANGE;
  }
  
  return GameCoreStates::CHANGE;
}

GameCoreStates::ConditionsPlayerRunning GameCoreStates::PlayerState::checkIfPlayerIsRunning(
                                InputMapping::Controller& controller, std::list<InputMapping::Key> keys)
{
  bool directionButtonPressed = false;
  bool directionButtonRightPressed = false;
  bool directionButtonLeftPressed = false;
  bool runningButtonPressed = false;

  GameCoreStates::ConditionsPlayerRunning isRunning;

  if ( keys.empty() )
  {
    isRunning.directionButtonPressed = false;
    isRunning.runningButtonPressed = false;
    return isRunning;
  }

  InputMapping::Key findKey = controller.getKeyAssociatedToState(GameCoreStates::WALKING, SpriteData::RIGHT);
  directionButtonRightPressed = findKey.isPressed;

  findKey = controller.getKeyAssociatedToState(GameCoreStates::WALKING, SpriteData::LEFT);
  directionButtonLeftPressed = findKey.isPressed;

  findKey = controller.getKeyAssociatedToState(GameCoreStates::RUNNING);
  isRunning.runningButtonPressed = findKey.isPressed;

  isRunning.directionButtonPressed = directionButtonRightPressed || directionButtonLeftPressed;

  return isRunning;
}

int GameCoreStates::PlayerState::checkMovementRestrictions(InputMapping::Controller& controller, int keyPreviouslyPressed, 
	                             int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  return checkMovement(controller, keyPreviouslyPressed, previousState, currentState, keys);
}

int GameCoreStates::PlayerState::checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, 
	                             int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  if ( currentState != previousState)
  {
    return GameCoreStates::CHANGE;
  }
  return GameCoreStates::NO_CHANGE;
}

