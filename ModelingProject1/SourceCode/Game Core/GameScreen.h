#pragma once

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

class GameScreen
{
  public:
   GameScreen(void);
   ~GameScreen(void);

   bool initializeScreen();
   bool initializeOpenGL();
   bool initializeSDLGLState();
   void initializeSDLFeatures();

   GLfloat getWidth();
   SDL_Surface& getScreenReference() { return *screen; }
    
  private:
   SDL_Surface* screen;
   int width, height;
   std::string windowName;
   const SDL_VideoInfo* defaultResolution;
};

