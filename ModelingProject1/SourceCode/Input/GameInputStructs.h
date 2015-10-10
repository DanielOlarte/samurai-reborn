#pragma once

#include "RawInputConstants.h"
#include "PlayerSpriteStates.h"
#include "GameInputContext.h"

#include <vector>
#include <set>

namespace InputMapping 
{
  struct MappedInput
  {
    std::set<GameCoreStates::Action> actions;
    std::vector<GameCoreStates::SpriteState> states;

    int directionKeyPressed;
    int buttonPreviouslyPressed;

    void eatAction(GameCoreStates::Action action);
    void eatStates();
  };
}