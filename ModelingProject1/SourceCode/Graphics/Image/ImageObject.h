#pragma once

#include <boost\noncopyable.hpp>

#include <windows.h>
#include <gl\GL.h>

#include <string>

#include "Vector.h"

namespace Image
{
  enum ImageState
  {
	DISABLE,
	ENABLE,
  };

  class ImageObject
  {
   public:
    ImageObject(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition);
    ImageObject(){};
	virtual ~ImageObject(){};

	virtual int getState() { return 0; };

    Vector2f getPosition() { return position; }
    void setPosition(GLfloat x, GLfloat y) { position = Vector2f(x, y); }

    Vector2f getOffset() { return offset; }

    Vector2f getTexturePosition() { return texturePosition; }

   protected:
    Vector2f position;
    Vector2f offset;
    Vector2f texturePosition;
  };
}