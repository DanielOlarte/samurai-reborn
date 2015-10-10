#pragma once

#include <TextObject.h>

namespace Text
{
  class ScoreText : public TextObject
  {
    public:
     ScoreText(std::string text, Vector2f pos, Vector2f off);
	 ScoreText() { }
	 ~ScoreText();

	 void initializeNumbersTexture(std::string filename);

	 GLuint getTextureNumbers() { return textureNumbers; }

	 void setDataText(int data);

    private:
	 GLuint textureNumbers;
  };
}