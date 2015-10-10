#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include "Player.h"

class Camera
{
  public:
   static Camera* getInstance();

   Camera();
   ~Camera();

   void initCamera(boost::ptr_vector< Characters::Player >* playerList);
    
   void renderCamera();

   bool checkCamera();
   void resetCamera(GLfloat level);
    
   void updateCamera();

   GLfloat getCameraPosition() { return posX; }
   void setCameraSpeed(GLfloat newSpeed) { speedX = newSpeed; }
   GLfloat getCameraSpeed() { return speedX; }

   bool isOnMidpoint(GLfloat posX);
   bool isLevelLimit(GLfloat position, GLfloat speedX);
   bool isCameraLimit(GLfloat speed);

  private:
    static bool instanceFlag;
    static Camera* camera;
	boost::ptr_vector< Characters::Player >* players;
    GLfloat posX;	
    GLfloat speedX;
    GLfloat midPoint;
    GLfloat interactionPoint;
    GLfloat levelLenght;
    bool onMidpoint;
    const SDL_VideoInfo* defaultResolution;
};