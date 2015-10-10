#pragma once

#include <windows.h>
#include <string>
#include <GL/gl.h>

#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

#include "GameText.h"

#include "GUIManager.h"

#include "Vector.h"

class GameRender
{
  public:
   GameRender(void);
   ~GameRender(void);

   static GLuint loadTexture(std::string name);
   static void drawFullTexture(GLuint texture, Vector2f pos, GLfloat widthTexture, GLfloat heightTexture);
   static void drawSpriteTexture(GLuint texture, Vector2f pos, int currentFrame,
                                 GLfloat widthSprite, GLfloat heightSprite,
                                 int direction = 0, int state = 0);
   static void drawSpecificTexture(GLuint texture, Vector2f pos, Vector2f offset, GLfloat widthDrawTexture, GLfloat heightDrawTexture);
   static void drawButton(GLuint texture, Vector2f pos, Vector2f dimensions, Vector2f offset);
   static void drawSoundBar(GLuint texture, Vector2f pos, Vector2f barDimensions, int currentFrame, int idState);
   static void drawLayerTexture(GLuint texture, Vector2f offset, GLfloat widthScreen, 
                                GLfloat heightScreen);
   static void drawText(Font::GameFont* font, Text::GameText text);

   RPRGUI::GUIManager* getGUIManager() { return guiManager; }

  private:
   RPRGUI::GUIManager* guiManager;
};

