#pragma once

#include "Enemy.h"

namespace Characters
{
  class JapaneseMonkey : public Enemy
  {
    public:
     ~JapaneseMonkey();
     void initializeCharacter(SpriteData::IDSprites id, std::string filename, Vector2f pos, int initialFrame, 
		                      std::vector < int > maxFrame, std::vector < int > returnFrame, GLfloat widthSprite, 
							  GLfloat heightSprite, std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement);

     void noAction();
     void walk();
     void run();
     void jump();
     void attack();
     void falling();
	 void stopping();
     void draw();
  };
}

