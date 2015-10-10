#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class FastAttackState : public PlayerState
  {
    public:
     FastAttackState(int id, int characterID);
     ~FastAttackState(void);

     int checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, int previousState, 
                      int currentState, std::list<InputMapping::Key> keys);
  };
}
