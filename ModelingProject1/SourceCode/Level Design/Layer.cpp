
#include "GameRender.h"
#include "Layer.h"

Layer::Layer(std::string name, GLfloat widthLayer, GLfloat heightLayer, Vector2f vel, 
          GLfloat constantX, bool hasRepetition, bool isContinuous)
{
  nameLayer = name;
  widthLevelLayer = widthLayer;
  heightLevelLayer = heightLayer;
  texture = GameRender::loadTexture(name);
  constantVelX = constantX;
  speed.x = vel.x;
  speed.y = vel.y;
  offset.x = offset.y = 0.0f;
  repeat = hasRepetition;
  continuous = isContinuous;
}

Layer::~Layer(void)
{
  glDeleteTextures(1, &texture);
}

void Layer::drawLayerTexture(GLfloat widthScreen, GLfloat heightScreen)
{
  GameRender::drawLayerTexture(texture, offset, widthScreen, heightScreen);
}

void Layer::setSpeedX(GLfloat velX)
{
  if ( !continuous )
  {
    speed.x = velX*constantVelX;
  }
}

void Layer::scrollLayer()
{
  offset.x += speed.x;
  offset.y += speed.y;

  checkScreenBoundaries();
}

bool Layer::checkScreenBoundaries()
{
  if (offset.x <= 0)
  {
    offset.x = 0;
    return false;
  }

  if (offset.x > widthLevelLayer - 1280.f)
  {
    if ( repeat )
    {
      return false;
    }

    offset.x = widthLevelLayer - 1280.f; 
    return true;
  }

  return false;
}

