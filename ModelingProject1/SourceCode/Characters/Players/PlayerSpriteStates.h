#pragma once

namespace GameCoreStates
{
  enum SpriteState
  {
    STILL,
    WALKING,
    JUMPING,
    RUNNING,
    DOUBLE_JUMP,
    FAST_ATTACK,
    FALLING,
  };

  enum Action
  {
	RIGHT,
	LEFT,
	CONTINUE,
	BACK,
	UP,
	DOWN,
	PAUSE,
	UNPAUSE,
  };

  enum ChangeStateResult
  {
    NO_CHANGE,
    CHANGE,
    UPDATE_SPEEDX,
  };
}

namespace Characters
{
  struct AttackData
  {
	bool attackAlreadyDamaged;
  };
}