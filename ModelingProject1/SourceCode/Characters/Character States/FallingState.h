#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class FallingState : public GameCoreStates::PlayerState
  {
   public:
    FallingState(int id);
    ~FallingState(void);

    int checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, int previousState, 
                      int currentState, std::list<InputMapping::Key> keys);
  };
}

