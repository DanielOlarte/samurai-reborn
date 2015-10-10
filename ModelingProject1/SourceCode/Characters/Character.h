#pragma once

#include <boost\noncopyable.hpp>

#include "Sprite.h"
#include "Weapon.h"

#include "Vector.h"

namespace Characters
{
  class Character 
  {
    public:
     virtual ~Character() { };

     virtual void initializeCharacter(SpriteData::IDSprites id, std::string filename, Vector2f pos, int initialFrame, 
		                              std::vector < int > maxFrame, std::vector < int > returnFrame, GLfloat widthSprite, 
									  GLfloat heightSprite, std::vector < int > framerateAnimations, 
									  std::vector< Vector2f> delayMovement) = 0;
     virtual void noAction() = 0;
     virtual void walk() = 0;
     virtual void run() = 0;
     virtual void jump() = 0;
     virtual void falling() = 0;
     virtual void stop() = 0;

     virtual void returnToPreviousState() = 0;

     virtual void draw() = 0;

     virtual void executeAction() = 0;

	 virtual bool isAlive();

     void initializeSpriteCollisionBox(float width, float height, GLfloat offsetX, GLfloat offsetY);
	 void initializeWeaponCollisionBoxes(std::string filename);
	 void initializeRigidBodyVectors(std::vector< Vector2f > maxSpeed);

     bool isReadyToPace();
     bool isReadyToDoubleJump();
     bool isFalling();
     
     SpriteData::IDSprites getCharacterID() { return characterSprite->getID(); }

     Sprite* getCharacterSprite() { return characterSprite; }

	 Weapons::Weapon* getCharacterWeapon() { return characterWeapon; }

    protected:
     Sprite* characterSprite;
     Weapons::Weapon* characterWeapon;
  };
}

