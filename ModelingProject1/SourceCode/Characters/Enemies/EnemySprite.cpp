
#include "EnemySprite.h"

EnemySprite::EnemySprite(SpriteData::IDSprites id, std::string filename, Vector2f pos, 
                int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement) : Sprite(id, filename, pos, initialFrame, maxFrame,
                                                               returnFrame, widthSprite, heightSprite, framerateAnimations,
                                                               delayMovement)
{
}

void EnemySprite::changeStateSprite(GameCoreStates::PlayerState* newState, int keyPreviouslyPressed, 
                                    std::list<InputMapping::Key> keys, InputMapping::Controller& controller)
{
  /*int resultCheckingEqualStates = newState->checkIfEqualStates(controller, keys, getCurrentState(),
                                  getPreviousState(), newState, keyPreviouslyPressed);

  if ( resultCheckingEqualStates == GameCoreStates::NO_CHANGE )
  {
    return;
  }

  playerStateManager->changeState(newState);
  setSpeedX(rigidBody->getMaxSpeed().at(getCurrentState()).x);
  setSpeedY(rigidBody->getMaxSpeed().at(getCurrentState()).y);
  handlerAnimation->setCurrentStateForAnimation(getCurrentState());
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();

  int resultCheckingEqualStates = newState->checkIfEqualStates(controller, keys, getCurrentState(),
                                    getPreviousState(), newState, keyPreviouslyPressed);

  GameCoreStates::ConditionsPlayerRunning isPacing = playerStateManager->getObjectState().checkIfPlayerIsRunning(controller, keys);

  int directionAxis = handlerAnimation->returnAnimationDirectionAxisValue();

  bool resultAccelerationForce = rigidBody->updateAccelerationState(keys, isPacing, speed.x, getCurrentState(),
	                                        newState->getCurrentID(), directionAxis);

  if ( resultAccelerationForce )
  {
	return;
  }

  switch(resultCheckingEqualStates)
  {
    case GameCoreStates::UPDATE_SPEEDX:
    {
      if ( getSpeedX() == 0.0f )
      {
        playerStateManager->changePreviousState( GameCoreStates::WALKING );
        setSpeedX( directionAxis*(rigidBody->getMaxSpeed().at( GameCoreStates::WALKING ).x ) );
		rigidBody->setAccelerationState(GamePhysics::ACCELERATE);
      }
      return;
    }
    case GameCoreStates::NO_CHANGE:
    {
      return;
    }
  }

  int result = newState->checkMovementRestrictions(controller, keyPreviouslyPressed, getPreviousState(), 
                                                   getCurrentState(), keys );

  switch(result)
  {
    case GameCoreStates::NO_CHANGE:
    {
      return;
    }
    case GameCoreStates::CHANGE:
    {
      playerStateManager->changeState(newState);
      break;
    }
  }

  if ( getCurrentState() == GameCoreStates::WALKING && getSpeedX() == 0.0f )
  {
	setSpeedX( directionAxis*2.0f );
  }

  setSpeedY(rigidBody->getMaxSpeed().at(getCurrentState()).y);
  handlerAnimation->setCurrentStateForAnimation(getCurrentState());
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();*/
}
