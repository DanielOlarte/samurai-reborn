
#include "GameInputStructs.h"

void InputMapping::MappedInput::eatAction(GameCoreStates::Action action)
{
  actions.erase(action); 
}

void InputMapping::MappedInput::eatStates()
{
  states.clear();
}