
#pragma once

namespace CollisionSystem
{
  struct DirectionsMove
  {
    bool canMoveXRight;
    bool canMoveXLeft;
    bool canMoveYUp;
    bool canMoveYDown;

    void setCanMoveRight(bool moveXR);
    void setCanMoveLeft(bool moveXL);
    void setCanMoveUp(bool moveUp);
    void setCanMoveDown(bool moveDown);
  };

  struct CharacterMovement
  {
    bool playerMoveInX;
    bool playerMoveInY;
    bool playerMoveInXInCurrentFrame;
    bool playerMoveInYInCurrentFrame;

    void setMoveX(bool moveX);
    void setMoveY(bool moveY);
    void setMoveXFrame(bool moveX);
    void setMoveYFrame(bool moveY);
  };

  const float initialCheckingBox = 0.0f;
}