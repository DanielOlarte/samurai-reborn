
#include "MeerkatP2.h"

#include <Keyboard.h>
#include <Gamepad.h>

#include <Spear.h>

Characters::MeerkatP2::~MeerkatP2()
{
  delete characterSprite;
  delete characterWeapon;
  delete inputMapper;
  delete controller;
  delete stats;
  delete score;
}

void Characters::MeerkatP2::initializeCharacter(SpriteData::IDSprites id, std::string filename,
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
                std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
                std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  characterSprite = new PlayerSprite(id, filename, pos, initialFrame, maxFrame, returnFrame,
                                     widthSprite, heightSprite, framerateAnimations, delayMovement);
  characterWeapon = new Weapons::Spear(100);
  
  stats = new PlayerStats::Stats();
  score = new PlayerScore::Score();

  attackData.attackAlreadyDamaged = false;
}

void Characters::MeerkatP2::noAction()
{
  characterSprite->setPlayerMoveInX(false);
  characterSprite->setPlayerMoveInY(false);
  characterSprite->setPlayerMoveInXCurrentFrame(false);
  stop();	
}

void Characters::MeerkatP2::walk()
{
  characterSprite->movePosXWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  characterSprite->setPlayerMoveInY(false);
  stop();
}

void Characters::MeerkatP2::run()
{
  characterSprite->movePosXWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  characterSprite->setPlayerMoveInY(false);
  stop();
}

void Characters::MeerkatP2::jump()
{
  characterSprite->setPlayerMoveInY(true);
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  stop();
}

void Characters::MeerkatP2::fastAttack()
{
  characterSprite->setPlayerMoveInY(true);
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();

  if ( characterSprite->getHandlerAnimation()->getAnimationAlreadyEnd() )
  {
	attackData.attackAlreadyDamaged = false;
    returnToPreviousState();
  }
  else
  {
    characterSprite->getHandlerAnimation()->animate(); 
  }
}

void Characters::MeerkatP2::falling()
{
  characterSprite->setPlayerMoveInY(true);
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();
  characterSprite->getHandlerAnimation()->animate();

  if ( !isFalling() )
  {
    stop();
  }
}

void Characters::MeerkatP2::draw()
{
  characterSprite->drawTexture();
}