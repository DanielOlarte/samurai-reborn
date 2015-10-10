#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class StillState : public PlayerState
  {
   public:
    StillState(int id);
    ~StillState(void);

    int checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, int previousState, 
                      int currentState, std::list<InputMapping::Key> keys);
  };
}
