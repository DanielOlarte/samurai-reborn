#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class RunningState : public PlayerState
  {
   public:
    RunningState(int id, int characterID);
    ~RunningState(void);

    int checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, int previousState, 
                      int currentState, std::list<InputMapping::Key> keys);
    int checkChangeOfState(InputMapping::Controller& controller, std::list<InputMapping::Key> keys, int currentState,
                           int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed);
  };
}
