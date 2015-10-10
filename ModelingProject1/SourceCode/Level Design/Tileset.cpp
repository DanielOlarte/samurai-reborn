
#include "Tileset.h"

Tileset::Tileset(int id, std::string name, GLfloat width, GLfloat height, GLfloat imageWidth, GLfloat imageHeight, 
                 int size, GLuint tex)
{
  ID = id;
  filename = name;
  widthTile = width;
  heightTile = height;
  widthImage = imageWidth;
  heightImage = imageHeight;
  numberOfTiles = size;
  texture = tex;
}

Tileset::~Tileset(void)
{
  glDeleteTextures(1, &texture);
}
