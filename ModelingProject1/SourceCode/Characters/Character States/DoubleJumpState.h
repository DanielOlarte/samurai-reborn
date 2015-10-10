#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class DoubleJumpState : public PlayerState
  {
   public:
    DoubleJumpState(int id);
    ~DoubleJumpState(void);

    int checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, int previousState, 
                      int currentState, std::list<InputMapping::Key> keys);
    int checkChangeOfState(InputMapping::Controller& controller, std::list<InputMapping::Key> keys, int currentState,
                           int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed);
  };
}