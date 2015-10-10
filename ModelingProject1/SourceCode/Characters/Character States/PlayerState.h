#pragma once

#include "State.h"
#include <Controller.h>
#include "GameSound.h"
#include "GameInputContext.h"

namespace GameCoreStates
{
  struct ConditionsPlayerRunning
  {
    bool directionButtonPressed;
    bool runningButtonPressed;
  };

  class PlayerState : public State
  {
   public:
	PlayerState(int id);
    PlayerState(int id, int characterID);
    PlayerState(){};
    ~PlayerState(){};

	int checkIfEqualStates(InputMapping::Controller& controller, std::list<InputMapping::Key> keys, 
		                   int currentState, int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed);
    int checkMovementRestrictions(InputMapping::Controller& controller, int keyPreviouslyPressed, int previousState, 
                                  int currentState, std::list<InputMapping::Key> keys);

    ConditionsPlayerRunning checkIfPlayerIsRunning(InputMapping::Controller& controller, std::list<InputMapping::Key> keys);

   protected:
	int characterID;
    virtual int checkMovement(InputMapping::Controller& controller, int keyPreviouslyPressed, int previousState, 
                              int currentState, std::list<InputMapping::Key> keys);
    virtual int checkChangeOfState(InputMapping::Controller& controller, std::list<InputMapping::Key> keys, int currentState,
                           int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed);
  };
}