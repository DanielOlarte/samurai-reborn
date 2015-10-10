#pragma once

#include "Character.h"

#include "EnemySprite.h"

enum AIState
{
	STATE_PATROL,
	STATE_CHASE,	
	STATE_RESET,
};

namespace Characters
{
  class Enemy : public Character
  {
    public:

     virtual void initializeCharacter(SpriteData::IDSprites id, std::string filename, Vector2f pos, int initialFrame, 
		                              std::vector < int > maxFrame, std::vector < int > returnFrame, GLfloat widthSprite, 
									  GLfloat heightSprite, std::vector < int > framerateAnimations,
									  std::vector< Vector2f> delayMovement) { };
     virtual void noAction() { };
     virtual void walk() { };
     virtual void run() { };
     virtual void jump() { };
     virtual void attack() { };
     virtual void falling() { };
     virtual void draw() { };

     void executeAction();
   
     void stop();

	 void setState(AIState newState);
	 AIState getState() {return state;}

     void returnToPreviousState();

    protected:
     int health;
     int modeIA;
     int pointsForDeath;
	 AIState state;
  };
}
