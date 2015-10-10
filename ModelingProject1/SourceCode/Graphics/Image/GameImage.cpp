#include "GameImage.h"

#include "GameRender.h"

Image::GameImage::GameImage(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, 
                            std::string filename)
{
  position = imagePosition;
  offset = imageOffset;
  this->texturePosition = texturePosition;
  texture = GameRender::loadTexture(filename);
  this->filename = filename;
}

Image::GameImage::GameImage(const Image::GameImage& cSource)
{
  position = cSource.position;
  offset = cSource.offset;
  texturePosition = cSource.texturePosition;
  filename = cSource.filename;
}

Image::GameImage& Image::GameImage::operator=(const Image::GameImage& cSource)
{
  position = cSource.position;
  offset = cSource.offset;
  texturePosition = cSource.texturePosition;
  filename = cSource.filename;

  return *this;
}

Image::GameImage::~GameImage(void)
{
  glDeleteTextures(1, &texture);
}
