
#include <algorithm>

#include "DoubleJumpState.h"

GameCoreStates::DoubleJumpState::DoubleJumpState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::DoubleJumpState::~DoubleJumpState(void)
{
}

int GameCoreStates::DoubleJumpState::checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, 
	                                 int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  InputMapping::Key findKey = controller.getKeyAssociatedToState(GameCoreStates::JUMPING);
  bool jumpingButtonIsPressed = findKey.isPressed;

  if ( currentState == GameCoreStates::JUMPING && previousState != GameCoreStates::DOUBLE_JUMP && 
       keyPreviouslyPressed == InputMapping::RAW_INPUT_NO_BUTTON && jumpingButtonIsPressed)
  {
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}

int GameCoreStates::DoubleJumpState::checkChangeOfState(InputMapping::Controller& controller, std::list<InputMapping::Key> keys, 
	                       int currentState, int previousState, GameCoreStates::PlayerState* newState, int keyPreviouslyPressed)
{
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(controller, keys);

  if ( currentState == GameCoreStates::DOUBLE_JUMP && isPacing.directionButtonPressed )
  {
    return GameCoreStates::UPDATE_SPEEDX;
  }

  if ( currentState != previousState)
  {
    return GameCoreStates::CHANGE;
  }
  return GameCoreStates::NO_CHANGE;
}