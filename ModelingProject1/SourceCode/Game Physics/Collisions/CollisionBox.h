#pragma once

#include "SDL/SDL_image.h"
#include "Vector.h"

namespace CollisionSystem
{
  class CollisionBox
  {
    public:
	 CollisionBox(){};
     CollisionBox(float x, float y ,float w, float h, Vector2f offset);
     ~CollisionBox(void);

     float getX() { return box.x; }
     void setX(float x, int direction);

     float getY() { return box.y; }
     void setY(float y);

     float getHeight() { return box.h; }
     float getWidth() { return box.w; }

	 void setBoxYBasedOnSpeed(float y);

     Vector2f getOffset() { return offsetBox; }
     GLfloat getOffsetXBasedOnDirection(int direction);

    private:
     SDL_Rect box;
     Vector2f offsetBox;
  };
}