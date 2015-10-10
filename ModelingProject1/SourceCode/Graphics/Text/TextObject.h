#pragma once

#include "Vector.h"

#include <string>

namespace Text
{
  class TextObject
  {
    public:
     TextObject(){};
     virtual ~TextObject();

     std::string getDataText() { return dataText; }

     Vector2f getPosition() { return position; }

     Vector2f getOffset() { return offset; }
     void setOffset(Vector2f off) { offset = off; }

     virtual void setDataText(int data) = 0;
	 virtual void setDataText(std::string data) { dataText = data; }

    protected:
	 TextObject(std::string text, Vector2f pos, Vector2f off);
     std::string dataText;
     Vector2f position;
     Vector2f offset;
  };
}
