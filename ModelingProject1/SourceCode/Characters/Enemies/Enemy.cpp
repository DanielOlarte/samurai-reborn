
#include "Enemy.h"

void Characters::Enemy::executeAction()
{
  switch( characterSprite->getCurrentState() )
  {
    case GameCoreStates::STILL:
    {
      noAction();
      break;
    }
    case GameCoreStates::WALKING:
    {
      walk();
      break;
    }
    case GameCoreStates::RUNNING:
    {
      run();
      break;
    }
    case GameCoreStates::JUMPING:
    case GameCoreStates::DOUBLE_JUMP:
    {
      jump();
      break;
    }
    case GameCoreStates::FAST_ATTACK:
    {
      attack();
      break;
    }
  }
}

void Characters::Enemy::stop()
{
  if ( !characterSprite->getPlayerMoveInX() && !characterSprite->getPlayerMoveInY() )
  {
    characterSprite->changeStateSprite(STILL_STATE);
    characterSprite->changeCurrentFrame(GameCoreStates::STILL);
  }
}

void Characters::Enemy::returnToPreviousState()
{
  switch( characterSprite->getPreviousState() )
  {
    case GameCoreStates::WALKING:
    {
      characterSprite->changeStateSprite(WALKING_STATE);
    }
  }

  characterSprite->changeCurrentFrame( characterSprite->getCurrentState() ); 
}
