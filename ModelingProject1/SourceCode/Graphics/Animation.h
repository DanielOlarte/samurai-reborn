#pragma once

#include "SDL/SDL.h"
#include <vector>

#include "SpriteDataConstants.h"

class Animation
{
  public:
   Animation(int actualFrame, int currentState, SpriteData::AnimationDirection direction, std::vector< int > maxFrames,
              std::vector< int > returnFrames, std::vector< int > framerates);
   ~Animation(void);
 
   int animate();

   void pauseAnimation();
   void unpauseAnimation();

   int getTicks();

   bool getAnimationAlreadyEnd() { return animationAlreadyEnd; }
   void restartAnimationBegin() { animationAlreadyEnd = false; }
 
   int getCurrentFrame() { return currentFrame; }
   void setCurrentFrame(int frame);
   void restartCurrentFrame() { currentFrame = returnFramesPerAnimation.at(currentState); }

   void setCurrentStateForAnimation(int state);

   void restartOldTime();

   int getAnimationDirection() { return animationDirectionX; }
   int changeAnimationDirection(int direction);
   int returnAnimationDirectionAxisValue();

   int getDirectionY() { return animationDirectionY; }
   void changeDirectionY(float speed);

  private:
   int currentFrame, incrementFrame;
   int currentState;
   Uint32 oldTime, currentTicks;
   bool animationAlreadyEnd, wasPaused;
   int animationDirectionX, animationDirectionY;
   std::vector< int > maxFramesPerAnimation;
   std::vector< int > returnFramesPerAnimation;
   std::vector< int > frameratePerAnimation;
};

