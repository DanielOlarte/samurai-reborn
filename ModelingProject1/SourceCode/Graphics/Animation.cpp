
#include "Animation.h"

Animation::Animation(int actualFrame, int currentState, SpriteData::AnimationDirection direction, 
                     std::vector< int > maxFrames, std::vector< int > returnFrames, std::vector< int > framerates)
{
  currentFrame = actualFrame;
  this->currentState = currentState;
  animationDirectionX = direction;
  animationDirectionY = SpriteData::DOWN;
  incrementFrame = 1;
  oldTime = currentTicks = SDL_GetTicks();
  animationAlreadyEnd = false;

  maxFramesPerAnimation = maxFrames;
  returnFramesPerAnimation = returnFrames;
  frameratePerAnimation = framerates;
}

Animation::~Animation(void)
{
  maxFramesPerAnimation.clear();
  returnFramesPerAnimation.clear();
  frameratePerAnimation.clear();
}

int Animation::animate() 
{
  currentTicks = getTicks();

  if( oldTime + frameratePerAnimation.at(currentState) > currentTicks ) 
  {
    return -1;
  }

  oldTime += frameratePerAnimation.at(currentState);

  animationAlreadyEnd = false;
  if ( maxFramesPerAnimation.at(currentState) > 0 )
  {
    currentFrame += incrementFrame;
    if( currentFrame > maxFramesPerAnimation.at(currentState) )
    {
      animationAlreadyEnd = true;
      currentFrame = returnFramesPerAnimation.at(currentState);
    }
  }

  return currentFrame;
}

void Animation::pauseAnimation()
{
  wasPaused = false;
}

void Animation::unpauseAnimation()
{
  wasPaused = true;
}

int Animation::getTicks()
{
  if( wasPaused == true )
  {
    restartOldTime();
	return currentTicks;
  }

  return SDL_GetTicks();
}

void Animation::setCurrentStateForAnimation(int state)
{
  currentState = state;
}

void Animation::setCurrentFrame(int frame)
{
  if( frame < 0 || frame > maxFramesPerAnimation.at(currentState)) 
  {
    currentFrame = returnFramesPerAnimation.at(currentState);
    return;
  }
 
  currentFrame = frame;
}

void Animation::restartOldTime()
{
  int differenceBetweenTicks = SDL_GetTicks() - currentTicks;
  oldTime += differenceBetweenTicks;
  currentTicks += differenceBetweenTicks;
  wasPaused = false;
}

int Animation::changeAnimationDirection(int direction)
{
  if ( animationDirectionX != direction )
  {
    animationDirectionX = direction;
    return -1;
  }

  return 1;
}

int Animation::returnAnimationDirectionAxisValue()
{
  if ( animationDirectionX == SpriteData::LEFT )
  {
    return -1;
  }
  return 1;
}

void Animation::changeDirectionY(float speed)
{
  if ( speed >= 0.0f )
  {
    animationDirectionY = SpriteData::DOWN;
    return;
  }
  else if ( speed < 0.0f )
  {
    animationDirectionY = SpriteData::UP;
    return;
  }
}


