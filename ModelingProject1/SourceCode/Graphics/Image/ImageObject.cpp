#include "ImageObject.h"

Image::ImageObject::ImageObject(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition)
{
  position = imagePosition;
  offset = imageOffset;
  this->texturePosition = texturePosition;
}
