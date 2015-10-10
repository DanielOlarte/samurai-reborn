
#include "CollisionStructs.h"

void CollisionSystem::DirectionsMove::setCanMoveRight(bool moveXR)
{
  canMoveXRight = moveXR;
}

void CollisionSystem::DirectionsMove::setCanMoveLeft(bool moveXL)
{
  canMoveXLeft = moveXL;
}

void CollisionSystem::DirectionsMove::setCanMoveUp(bool moveUp)
{
  canMoveYUp = moveUp;
}

void CollisionSystem::DirectionsMove::setCanMoveDown(bool moveDown)
{
  canMoveYDown = moveDown;
}

void CollisionSystem::CharacterMovement::setMoveX(bool moveX)
{
  playerMoveInX = moveX;
}

void CollisionSystem::CharacterMovement::setMoveY(bool moveY)
{
  playerMoveInY = moveY;
}

void CollisionSystem::CharacterMovement::setMoveXFrame(bool moveX)
{
  playerMoveInXInCurrentFrame = moveX;
}

void CollisionSystem::CharacterMovement::setMoveYFrame(bool moveY)
{
  playerMoveInYInCurrentFrame = moveY;
}