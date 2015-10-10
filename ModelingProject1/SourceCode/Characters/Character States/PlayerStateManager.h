#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "State.h"
#include "PlayerState.h"
#include "StillState.h"
#include "WalkingState.h"
#include "RunningState.h"
#include "JumpingState.h"
#include "DoubleJumpState.h"
#include "FastAttackState.h"
#include "FallingState.h"

#include "PlayerSpriteStates.h"

#define STILL_STATE new GameCoreStates::StillState(GameCoreStates::STILL)
#define WALKING_STATE new GameCoreStates::WalkingState(GameCoreStates::WALKING)
#define JUMPING_STATE(characterID) new GameCoreStates::JumpingState(GameCoreStates::JUMPING, characterID)
#define RUNNING_STATE(characterID) new GameCoreStates::RunningState(GameCoreStates::RUNNING, characterID)
#define DOUBLE_JUMP_STATE new GameCoreStates::DoubleJumpState(GameCoreStates::DOUBLE_JUMP)
#define FAST_ATTACK_STATE(characterID) new GameCoreStates::FastAttackState(GameCoreStates::FAST_ATTACK, characterID)
#define FALLING_STATE new GameCoreStates::FallingState(GameCoreStates::FALLING)

namespace GameCoreStates
{
  class PlayerStateManager
  {
    public:
     PlayerStateManager(void);
     ~PlayerStateManager(void);

     void pushState( GameCoreStates::PlayerState* playerState );
     void popState();
     void changeState( GameCoreStates::PlayerState* newState );
     void changePreviousState( GameCoreStates::SpriteState previousID );

     int getCurrentState() { return currentState.getCurrentID(); }
     GameCoreStates::PlayerState getObjectState() { return currentState; }
     int getPreviousState() { return previousState; }

    private:
     boost::ptr_vector< State > statesStack;
     GameCoreStates::SpriteState previousState;
     GameCoreStates::PlayerState currentState;
  };
}

