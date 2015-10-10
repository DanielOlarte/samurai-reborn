
#include <algorithm>

#include "FastAttackState.h"

#include <GameSound.h>

GameCoreStates::FastAttackState::FastAttackState(int id, int characterID) : PlayerState(id, characterID)
{
}

GameCoreStates::FastAttackState::~FastAttackState(void)
{
}

int GameCoreStates::FastAttackState::checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, 
	                                 int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(controller, keys);
  InputMapping::Key findKey = controller.getKeyAssociatedToState(GameCoreStates::FAST_ATTACK);
  bool fastAttackButtonIsPressed = findKey.isPressed;

  if ( (currentState != GameCoreStates::DOUBLE_JUMP && currentState != GameCoreStates::FALLING) &&
       keyPreviouslyPressed == InputMapping::RAW_INPUT_NO_BUTTON && fastAttackButtonIsPressed )
  {
    if (currentState == GameCoreStates::STILL)
    {
	  GameSound::getInstance()->loadChunk(characterID, 0, 3);
    }
    else
    {
	  GameSound::getInstance()->loadChunk(characterID, 0, 0);
	}
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}