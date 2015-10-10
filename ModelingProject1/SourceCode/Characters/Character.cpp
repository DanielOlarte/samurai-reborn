
#include "Character.h"

void Characters::Character::initializeSpriteCollisionBox(float width, float height, GLfloat offsetX, GLfloat offsetY)
{
  characterSprite->initializeSpriteCollisionBox(width, height, offsetX, offsetY);
}

void Characters::Character::initializeWeaponCollisionBoxes(std::string filename)
{
  characterSprite->initializeWeaponCollisionBoxes(filename);
}

void Characters::Character::initializeRigidBodyVectors(std::vector< Vector2f > maxSpeed)
{
  characterSprite->getRigidBody().initializeSpeedVectors(maxSpeed);
}

bool Characters::Character::isReadyToPace()
{
  if ( characterSprite->getCurrentState() != GameCoreStates::JUMPING &&
       characterSprite->getCurrentState() != GameCoreStates::DOUBLE_JUMP && 
       characterSprite->getCurrentState() != GameCoreStates::FALLING )
  {
    return true;
  }

  return false;
}

bool Characters::Character::isReadyToDoubleJump()
{
  GLfloat speedForDoubleJump = characterSprite->getRigidBody().getMaxSpeed().at(GameCoreStates::JUMPING).y;
  if ( characterSprite->getSpeedY() >= speedForDoubleJump/1.5f && characterSprite->getSpeedY() <= 0 )
  {
    return true;
  }

  return false;
}

bool Characters::Character::isFalling()
{
  if ( characterSprite->getIsOnGround() )
  {
    return false;
  }

  if ( characterSprite->getSpeedY() >= 0)
  {
    return true;
  }

  return false;
}

bool Characters::Character::isAlive()
{
  if ( characterSprite->getBoxY() > 720.0f )
  {
    return false;
  }

  return true;
}