
#include "Camera.h"

#define GRAB_CAMERA_RANGE 40
#define RELEASE_CAMERA_RANGE 300

bool Camera::instanceFlag = false;
Camera* Camera::camera = NULL;

Camera* Camera::getInstance()
{
  if( !instanceFlag )
  {
    camera = new Camera();
    instanceFlag = true;
  }
  return camera;
}

Camera::Camera()
{
  posX = 0.0f;
  speedX = 0.0f;	
  midPoint = 0.0f;	
  onMidpoint = false;
}

Camera::~Camera()
{
}

void Camera::initCamera(boost::ptr_vector< Characters::Player >* playerList)
{
  players = playerList;
  defaultResolution = SDL_GetVideoInfo();
  midPoint = (GLfloat)defaultResolution->current_w/2;
}

void Camera::renderCamera()
{
  glTranslatef(-posX, 0, 0);
}

void Camera::updateCamera()
{ 	
  if( players->size() == 1 )
  {
    GLfloat playerPosition = players->at(0).getCharacterSprite()->getBoxX() + players->at(0).getCharacterSprite()->getBoxWidth()/2;
    speedX = playerPosition - interactionPoint;
    interactionPoint = playerPosition;
  }
  else if(players->size() > 1)
  {
    GLfloat minPosition = std::numeric_limits<float>::max();
    GLfloat maxPosition = -std::numeric_limits<float>::max();
    
    for(unsigned i = 0; i < players->size(); i++)
    {
      if( players->at(i).getCharacterSprite()->getBoxX() > maxPosition )
      {
        maxPosition = players->at(i).getCharacterSprite()->getBoxX();
      }
      if( players->at(i).getCharacterSprite()->getBoxX() < minPosition )
      {
		minPosition = players->at(i).getCharacterSprite()->getBoxX();
      }
    }
    speedX = ( (maxPosition + minPosition)/2 ) - interactionPoint;
    interactionPoint = (maxPosition + minPosition)/2;
  }

  if( !checkCamera() || !isOnMidpoint(interactionPoint) )
  {
    speedX = 0.0f;
    onMidpoint = false;
  }
  else
  {
    midPoint += speedX;
    posX += speedX;
  }
}

bool Camera::checkCamera()
{	
  for(unsigned i = 0; i < players->size(); i++)
  {
    if( isLevelLimit( posX, players->at(i).getCharacterSprite()->getSpeedX() ) ||
        isLevelLimit( posX + (GLfloat)defaultResolution->current_w, players->at(i).getCharacterSprite()->getSpeedX() ) )
    {
      return false;
    }	
  }

  return true;
}


void Camera::resetCamera(GLfloat level)
{
  posX = 0.0f;
  speedX = 0.0f;	
  levelLenght = level;
  onMidpoint = false;
  midPoint = (GLfloat)defaultResolution->current_w/2;

  if( players->size() == 1 )
  {
    interactionPoint=players->at(0).getCharacterSprite()->getBoxX() + players->at(0).getCharacterSprite()->getBoxWidth()/2; 
  }

  else if(players->size() > 1)
  {
	GLfloat minPosition = std::numeric_limits<float>::max();
    GLfloat maxPosition = -std::numeric_limits<float>::max();
    unsigned iMax = 0,iMin = 0;

    for(unsigned i = 0; i < players->size(); i++)
    {
      if( players->at(i).getCharacterSprite()->getBoxX() > maxPosition )
      {
		maxPosition = players->at(i).getCharacterSprite()->getBoxX();
		iMax = i;
      }
      if( players->at(i).getCharacterSprite()->getBoxX() < minPosition )
      {
		minPosition = players->at(i).getCharacterSprite()->getBoxX();
		iMin = i;
      }
    }
    interactionPoint=(players->at(iMin).getCharacterSprite()->getBoxX() + players->at(iMax).getCharacterSprite()->getBoxX() )/2;
  }
}

bool Camera::isOnMidpoint(GLfloat posX)
{
  int distanceToMid = abs((int)posX - (int)midPoint);
  if( onMidpoint )
  {
    if( distanceToMid < RELEASE_CAMERA_RANGE )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    if( distanceToMid < GRAB_CAMERA_RANGE )
    {
      onMidpoint = true;
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool Camera::isLevelLimit(GLfloat position, GLfloat speed)
{
  if( position + speed < 0 || position + speed > levelLenght)
  {
    return true;
  }
  return false;
}

bool Camera::isCameraLimit(GLfloat speed)
{
  bool isLimit = false;
  for(unsigned i = 0; i < players->size(); i++)
  {
    GLfloat boxX = players->at(i).getCharacterSprite()->getBoxX();
    GLfloat boxWidth = players->at(i).getCharacterSprite()->getBoxWidth();
    GLfloat cameraWidth = (GLfloat)defaultResolution->current_w;
    int direction = players->at(i).getCharacterSprite()->getHandlerAnimation()->getAnimationDirection();

	switch(direction)
	{
	  case SpriteData::LEFT:
	  {
	    if( (posX - speed > boxX || posX + cameraWidth - speed <  boxX + boxWidth) && 
			 boxX != levelLenght - boxWidth)
		{ 
		  isLimit = true;
	    }
		break;
      }
	  case SpriteData::RIGHT:
	  {
	    if( (posX + speed > boxX || posX + cameraWidth + speed <  boxX + boxWidth) && 
			 boxX != 0.0f)
		{ 
		  isLimit = true;
		}
		break;
      }
    }
  }
  return isLimit;
}