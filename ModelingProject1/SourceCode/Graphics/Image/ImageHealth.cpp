
#include <ImageHealth.h>

Image::ImageHealth::ImageHealth(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, int max)
{
  position = imagePosition;
  offset = imageOffset;
  this->texturePosition = texturePosition;
  maxAmount = max;
  currentAmount = max;
}