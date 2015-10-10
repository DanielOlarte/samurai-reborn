
#include "Camera.h"

#define GRAB_CAMERA_RANGE 40
#define RELEASE_CAMERA_RANGE 250

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

void Camera::initCamera()
{
  defaultResolution = SDL_GetVideoInfo();
  midPoint = (GLfloat)defaultResolution->current_w/2;
}

void Camera::renderCamera()
{
  glTranslatef(-posX, 0, 0);
}

void Camera::updateCamera(boost::ptr_vector<Characters::Player>* players)
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
      if( players->at(i).getCharacterSprite()->getPosX() > maxPosition )
      {
        maxPosition = players->at(i).getCharacterSprite()->getPosX();
      }
      else if( players->at(i).getCharacterSprite()->getPosX() < minPosition )
      {
        minPosition = players->at(i).getCharacterSprite()->getPosX();
      }
    }
    speedX = ( (maxPosition - minPosition)/2 ) - interactionPoint;
    interactionPoint = (maxPosition - minPosition)/2;
  }

  if( !checkCamera(players) || !isOnMidpoint(interactionPoint) )
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

bool Camera::checkCamera(boost::ptr_vector<Characters::Player>* players)
{	
  for(unsigned i = 0; i < players->size(); i++)
  {
    if( isLimit( posX, players->at(i).getCharacterSprite()->getSpeedX() ) ||
        isLimit( posX + (GLfloat)defaultResolution->current_w, players->at(i).getCharacterSprite()->getSpeedX() ) )
    {
      return false;
    }	
  }

  return true;
}


void Camera::resetCamera(GLfloat level, GLfloat spawningPoint)
{
  posX = 0.0f;
  speedX = 0.0f;	
  levelLenght = level;
  onMidpoint = false;
  midPoint = (GLfloat)defaultResolution->current_w/2;
  interactionPoint = spawningPoint;
}

bool Camera::isOnMidpoint(GLfloat posX)
{
  GLfloat distanceToMid = abs(posX - midPoint);
  if( onMidpoint )
  {	
    if( distanceToMid < RELEASE_CAMERA_RANGE )
    {
	  onMidpoint = true;
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

bool Camera::isLimit(GLfloat position, GLfloat speed)
{
  if( position + speed < -15 || position + speed > levelLenght )
  {
    return true;
  }
  return false;
}