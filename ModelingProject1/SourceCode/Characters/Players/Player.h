#pragma once

#include "Character.h"

#include "PlayerSprite.h"
#include "Stats.h"
#include "Score.h"
#include "GameInputMapper.h"

#include <Controller.h>

namespace Characters
{
  class Player : public Character
  {
    public:
     virtual ~Player() { };

     virtual void initializeCharacter(SpriteData::IDSprites id, std::string filename, Vector2f pos, int initialFrame, 
		                              std::vector < int > maxFrame, std::vector < int > returnFrame, GLfloat widthSprite, 
									  GLfloat heightSprite, std::vector < int > framerateAnimations, 
									  std::vector< Vector2f> delayMovement) { };
     virtual void noAction() { };
     virtual void walk() { };
     virtual void run() { };
     virtual void jump() { };
     virtual void fastAttack() { };
     virtual void falling() { };
     virtual void draw() { };

     void executeAction();
   
     void stop();

     void returnToPreviousState();

	 bool isAlive();

	 void updateStats();

     void drawUIStats();
     void drawScore();
      
     static void inputCallback(InputMapping::MappedInput& inputs, Player& player, 
		                       std::list<InputMapping::Key> keys, Image::MenuSelection& menu);

	 void setIDNumberOfPlayer(int id) { idNumberOfPlayer = id; }

     InputMapping::GameInputMapper* getInputMapper() { return inputMapper; }
	 void setGameInputMapper(InputMapping::GameInputMapper* mapper) { inputMapper = mapper; }

	 InputMapping::Controller* getController() { return controller; }
	 void setController(InputMapping::Controller* control) { controller = control; }

     PlayerStats::Stats* getPlayerStats() { return stats; }

     PlayerScore::Score* getScore() { return score; }

	 AttackData getAttackData() { return attackData; }
	 void setAttackAlreadyDamaged(bool attack) { attackData.attackAlreadyDamaged = attack; }

    protected:
	 int idNumberOfPlayer;
     InputMapping::GameInputMapper* inputMapper;
	 InputMapping::Controller* controller;
     PlayerStats::Stats* stats;
     PlayerScore::Score* score;
	 AttackData attackData;
  };
}