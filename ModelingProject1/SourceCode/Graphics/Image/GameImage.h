#pragma once

#include <ImageObject.h>

namespace Image
{
  class GameImage : public ImageObject
  {
   public:
    GameImage(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, std::string filename);
    GameImage(){};
    
	GameImage(const GameImage& cSource);
    GameImage& operator=(const GameImage& cSource);
    ~GameImage(void);

    GLuint getTexture() { return texture; }

   private:
    GLuint texture;
	std::string filename;
  };
}