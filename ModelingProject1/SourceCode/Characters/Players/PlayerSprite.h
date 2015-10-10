#pragma once

#include "Sprite.h"

class PlayerSprite : public Sprite
{
  public:
   PlayerSprite(SpriteData::IDSprites id, std::string filename, Vector2f pos, int initialFrame, 
	            std::vector < int > maxFrame, std::vector < int > returnFrame, GLfloat widthSprite, 
				GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement);

   void changeStateSprite( GameCoreStates::PlayerState* newState, int keyPreviouslyPressed = 0, 
	                       std::list<InputMapping::Key> keys = std::list<InputMapping::Key>(),
						   InputMapping::Controller& controller = InputMapping::Controller() );
};

