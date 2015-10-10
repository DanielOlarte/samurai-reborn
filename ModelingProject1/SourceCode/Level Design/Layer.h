#pragma once

#include <windows.h>
#include <GL/gl.h>

#include <string>

#include "Vector.h"

class Layer
{
  public:
   Layer(std::string name, GLfloat widthLayer, GLfloat heightLayer, Vector2f vel, 
         GLfloat constantX, bool hasRepetition, bool isContinuous);
   ~Layer(void);

   void drawLayerTexture(GLfloat widthScreen, GLfloat heightScreen);
    
   GLuint getTexture() { return texture; }
   void setLayerTexture(GLuint layerTexture) { texture = layerTexture; }

   GLfloat getWidthLevelLayer() { return widthLevelLayer; }
   void setWidthLevelLayer(GLfloat width) { widthLevelLayer = width; }

   GLfloat getHeightLevelLayer() { return heightLevelLayer; }
   void setHeightLevelLayer(GLfloat height) { heightLevelLayer = height; }

   GLfloat getSpeedX() { return speed.x; }
   void setSpeedX(GLfloat velX);

   void scrollLayer();

   GLfloat getOffsetX() { return offset.x; }
   void setOffsetX(GLfloat velX) { offset.x = velX; }

   GLfloat getOffsetY() { return offset.y; }

   bool checkScreenBoundaries();

   bool getRepeat() { return repeat; }
   void setRepeat(bool hasRepetition) { repeat = hasRepetition; }

   bool getIsContinuous() { return continuous; }

  private:
   std::string nameLayer;
   GLuint texture;
   GLfloat widthLevelLayer, heightLevelLayer;
   Vector2f speed, offset;
   GLfloat constantVelX;
   bool repeat;
   bool continuous;
};