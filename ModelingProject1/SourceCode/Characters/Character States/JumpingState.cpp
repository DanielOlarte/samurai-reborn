
#include <algorithm>

#include "JumpingState.h"

GameCoreStates::JumpingState::JumpingState(int id, int characterID) : PlayerState(id, characterID)
{
}

GameCoreStates::JumpingState::~JumpingState(void)
{
}

int GameCoreStates::JumpingState::checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, 
	                                 int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  InputMapping::Key findKey = controller.getKeyAssociatedToState(GameCoreStates::JUMPING);
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(controller, keys);
  bool jumpingButtonIsPressed = findKey.isPressed;

  if ( keyPreviouslyPressed != InputMapping::RAW_INPUT_NO_BUTTON && !jumpingButtonIsPressed )
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( jumpingButtonIsPressed && findKey.wasPreviouslyPressed )
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( ( currentState != GameCoreStates::JUMPING  && currentState != GameCoreStates::DOUBLE_JUMP
                                                  && currentState != GameCoreStates::FALLING
                                                  && currentState != GameCoreStates::FAST_ATTACK ) || 
       ( previousState == GameCoreStates::JUMPING && currentState == GameCoreStates::STILL ) )
  {
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}

int GameCoreStates::JumpingState::checkChangeOfState(InputMapping::Controller& controller, std::list<InputMapping::Key> keys,
	                       int currentState, int previousState, GameCoreStates::PlayerState* newState, int keyPreviouslyPressed)
{
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(controller, keys);

  if ( currentState == GameCoreStates::JUMPING && isPacing.directionButtonPressed )
  {
    return GameCoreStates::UPDATE_SPEEDX;
  }

  if ( currentState != previousState)
  {
    return GameCoreStates::CHANGE;
  }
  return GameCoreStates::NO_CHANGE;
}
