
#include <algorithm>

#include "Player.h"
#include <GameStatesData.h>

void Characters::Player::executeAction()
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
      fastAttack();
      break;
    }
    case GameCoreStates::FALLING:
    {
      falling();
      break;
    }
  }
}

void Characters::Player::stop()
{
  if ( characterSprite->getSpeedX() == 0.0f && characterSprite->getSpeedY() == 0.0f &&
	   !characterSprite->isPlayerOnTheAir())
  {
    characterSprite->changeStateSprite(STILL_STATE, 0, getInputMapper()->getListKeys());
    getInputMapper()->pushBackStateOnMappedInput(GameCoreStates::STILL);
    characterSprite->changeCurrentFrame(GameCoreStates::STILL);
	characterSprite->getRigidBody().setAccelerationState(GamePhysics::NO_ACCELERATE);
  }
}

void Characters::Player::returnToPreviousState()
{
  switch( characterSprite->getPreviousState() )
  {
    case GameCoreStates::STILL:
    {
      characterSprite->changeStateSprite(STILL_STATE, 0, getInputMapper()->getListKeys());
      break;
    }
    case GameCoreStates::WALKING:
    {
      characterSprite->changeStateSprite(WALKING_STATE, 1, getInputMapper()->getListKeys());
      break;
    }
    case GameCoreStates::RUNNING:
    {
      characterSprite->changeStateSprite(RUNNING_STATE(characterSprite->getID()), 1, getInputMapper()->getListKeys());
      break;
    }
    case GameCoreStates::JUMPING:
    {
      characterSprite->changeStateSprite(FALLING_STATE, 0, getInputMapper()->getListKeys());
      break;
    }
  }

  getInputMapper()->pushBackStateOnMappedInput( GameCoreStates::SpriteState( characterSprite->getCurrentState() ) );
  characterSprite->changeCurrentFrame( characterSprite->getCurrentState() ); 
}

bool Characters::Player::isAlive()
{
  if ( stats->getHealth() <= 0 || characterSprite->getBoxY() > 720.0f )
  {
	return false;
  }

  return true;
}

void Characters::Player::updateStats()
{
  stats->updateHealthBar();
  stats->updateFaceState();
}

void Characters::Player::drawUIStats()
{
  stats->drawFaceState();
  stats->drawSkullKills();
  stats->drawHealthBar();
  stats->drawHealth();
}

void Characters::Player::drawScore()
{
  score->drawDisplayPoints();
}

void Characters::Player::inputCallback(InputMapping::MappedInput& inputs, Player& player, std::list<InputMapping::Key> keys,
	                                   Image::MenuSelection& menu)
{
  Sprite* playerSprite = player.getCharacterSprite();

  int previousDirectionX = playerSprite->getHandlerAnimation()->getAnimationDirection();
  playerSprite->setConstantSpeedX ( 
                playerSprite->getHandlerAnimation()->changeAnimationDirection(inputs.directionKeyPressed) );

  if ( previousDirectionX != playerSprite->getHandlerAnimation()->getAnimationDirection() )
  {
	return;
  }

  bool findStillInStates = find(inputs.states.begin(), inputs.states.end(), GameCoreStates::STILL) 
                           != inputs.states.end();
  bool findWalkingInStates = find(inputs.states.begin(), inputs.states.end(), GameCoreStates::WALKING) 
                             != inputs.states.end();
  bool findJumpingInStates = find(inputs.states.begin(), inputs.states.end(), GameCoreStates::JUMPING) 
                             != inputs.states.end();
  bool findRunningInStates = find(inputs.states.begin(), inputs.states.end(), GameCoreStates::RUNNING) 
                             != inputs.states.end();
  bool findFastAttackWalkingInStates = find(inputs.states.begin(), inputs.states.end(), 
                                       GameCoreStates::FAST_ATTACK) != inputs.states.end();

  bool findPauseAction = find(inputs.actions.begin(), inputs.actions.end(), GameCoreStates::PAUSE) != inputs.actions.end();

  InputMapping::Key checkKey = player.getController()->getKeyAssociatedToState(GameCoreStates::JUMPING);

  if ( findWalkingInStates && player.isReadyToPace() )
  {
    playerSprite->changeStateSprite(WALKING_STATE, inputs.buttonPreviouslyPressed, keys, *player.getController());
  }

  if ( findRunningInStates && player.isReadyToPace() )
  {
    playerSprite->changeStateSprite(RUNNING_STATE(playerSprite->getID()), inputs.buttonPreviouslyPressed, keys, *player.getController());
  }

  if ( findJumpingInStates )
  {
    playerSprite->changeStateSprite(JUMPING_STATE(playerSprite->getID()), checkKey.wasPreviouslyPressed, keys, *player.getController());

    if ( player.isReadyToDoubleJump() )
    {
      playerSprite->changeStateSprite(DOUBLE_JUMP_STATE, checkKey.wasPreviouslyPressed, keys, *player.getController());
    }

    if ( player.isFalling() )
    {
      playerSprite->changeStateSprite(FALLING_STATE, checkKey.wasPreviouslyPressed, keys, *player.getController());
    }
  }

  if ( findStillInStates )
  {
    playerSprite->changeStateSprite(STILL_STATE, inputs.buttonPreviouslyPressed, keys, *player.getController());
  }

  if ( findFastAttackWalkingInStates )
  {
    checkKey = player.getController()->getKeyAssociatedToState(GameCoreStates::FAST_ATTACK);
    playerSprite->changeStateSprite(FAST_ATTACK_STATE(playerSprite->getID()), checkKey.wasPreviouslyPressed, 
		                            keys, *player.getController());
  }

  if ( findPauseAction )
  {
    menu.setNewIdGameState(MainStates::STATE_PAUSE);
  }
}
