#pragma once

#include <windows.h>
#include <gl\GL.h>
#include <SDL/SDL.h>
#include "Vector.h"
#include "GameRender.h"

class LoadingScreen
{
  public:
   LoadingScreen(std::string nameLevel);
   ~LoadingScreen(void);

   void updateValues(int percentage);
   void renderScreen(int percentage);

  private:
   GLuint statusBarUnit;
   GLuint background;
   GLuint levelScreen;
   Vector2f statusBarPosition;
   Vector2f statusBarOffset;
   int statusBarWidth;
};

