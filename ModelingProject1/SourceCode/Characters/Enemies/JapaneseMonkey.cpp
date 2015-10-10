
#include "JapaneseMonkey.h"

void Characters::JapaneseMonkey::initializeCharacter(SpriteData::IDSprites id, std::string filename,
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
                std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
                std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  characterSprite = new EnemySprite(id, filename, pos, initialFrame, maxFrame, returnFrame,
                           widthSprite, heightSprite,framerateAnimations,delayMovement);
}

Characters::JapaneseMonkey::~JapaneseMonkey(){

}

void Characters::JapaneseMonkey::noAction()
{
  characterSprite->setSpeedX(0);
  characterSprite->setPlayerMoveInX(false);
  characterSprite->setPlayerMoveInY(false);
  stop();		
}

void Characters::JapaneseMonkey::walk()
{
  characterSprite->movePosXWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  characterSprite->setPlayerMoveInY(false);
  stop();
}

void Characters::JapaneseMonkey::run()
{
  /*enemySprite->setSpeedX( enemySprite->getStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->getHandlerAnimation()->animate();
  stop();*/
}

void Characters::JapaneseMonkey::jump()
{
  /*enemySprite->setPlayerMoveInY(true);
  enemySprite->setSpeedX( enemySprite->getPreviousStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->movePosYWithSpeed();
  enemySprite->getHandlerAnimation()->animate() ;
  stop();*/
}

void Characters::JapaneseMonkey::attack()
{
  /*enemySprite->setPlayerMoveInY(true);
  enemySprite->setSpeedX( enemySprite->getPreviousStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->movePosYWithSpeed();

  if ( enemySprite->getHandlerAnimation()->getAnimationAlreadyEnd() )
  {
    returnToPreviousState();
  }
  else
  {
    enemySprite->getHandlerAnimation()->animate(); 
  }*/
}

void Characters::JapaneseMonkey::falling()
{/*
  characterSprite->setPlayerMoveInY(true);
  characterSprite->setSpeedX( characterSprite->getPreviousStateXSpeed() );
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();
  characterSprite->getHandlerAnimation()->animate();

  if ( !isFalling() )
  {
    stop();
  }*/
}

void Characters::JapaneseMonkey::stopping()
{
  //
}

void Characters::JapaneseMonkey::draw()
{
  characterSprite->drawTexture();
}