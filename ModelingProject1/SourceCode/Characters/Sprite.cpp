
#include "Sprite.h"
#include "PlayerState.h"
#include "Collider.h"
#include "Camera.h"

#include <StringParser.h>

Sprite::Sprite(SpriteData::IDSprites id, std::string filename, Vector2f pos, 
                int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement)
{
  ID = id;
  texture = GameRender::loadTexture(filename);
  glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &this->widthTexture);
  glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &this->heightTexture);

  playerStateManager = new GameCoreStates::PlayerStateManager();

  handlerAnimation = new Animation(initialFrame, getCurrentState(), SpriteData::RIGHT, 
                                   maxFrame, returnFrame, framerateAnimations );

  rigidBody = new GamePhysics::RigidBody(GamePhysics::RIGID_BODY);
  rigidBody->initializeNaturalPhysicsForces(-5.5f, 1.0f);

  collisionHandler = Collider::getInstance();

  delayMovementSprite = delayMovement;

  width = widthSprite;	
  height = heightSprite;
  position.x = pos.x;		
  position.y = pos.y;

  speed = Vector2f(0.0f, 0.0f);

  countX = 0;
  countY = 0;

  characterMovement.playerMoveInXInCurrentFrame = false;
  characterMovement.playerMoveInYInCurrentFrame = false;
  characterMovement.playerMoveInX = false;
  characterMovement.playerMoveInY = false;
}

Sprite::~Sprite(void)
{
  glDeleteTextures(1, &texture);
  delayMovementSprite.clear();
  weaponCollisionBoxes.clear();

  delete rigidBody;
  delete playerStateManager;
  delete handlerAnimation;
  delete spriteCollisionBox;
}

void Sprite::initializeSpriteCollisionBox(float width, float height, GLfloat offsetX, GLfloat offsetY)
{
  spriteCollisionBox = new CollisionSystem::CollisionBox(0.0f, 0.0f, width, height, Vector2f(offsetX, offsetY));
  spriteCollisionBox->setX(position.x, handlerAnimation->getAnimationDirection());
  spriteCollisionBox->setY(position.y);

  textureBox = GameRender::loadTexture("boxPanda.png");
  //textureBox = GameRender::loadTexture("box.png"); //Meerkat

  changeStateSprite( new GameCoreStates::StillState(GameCoreStates::STILL), 0,
                         std::list< InputMapping::Key >() );
}

void Sprite::initializeWeaponCollisionBoxes(std::string filename)
{
  unsigned countBoxes;
    
  std::ifstream inputContextFile(filename);
  countBoxes = readDataTypeFromFile<unsigned>(inputContextFile);

  for(unsigned i = 0; i < countBoxes; i++)
  {
    std::string width = readDataTypeFromFile<std::string>(inputContextFile);
    std::string height = readDataTypeFromFile<std::string>(inputContextFile);
    std::string offsetX = readDataTypeFromFile<std::string>(inputContextFile);
    std::string offsetY = readDataTypeFromFile<std::string>(inputContextFile);

	int parseWidth = parsePointerStringToInt(width.c_str());
	int parseHeight = parsePointerStringToInt(height.c_str());
    int parseOffsetX = parsePointerStringToInt(offsetX.c_str());
	int parseOffsetY = parsePointerStringToInt(offsetY.c_str());

	weaponCollisionBoxes.push_back( new CollisionSystem::CollisionBox(0.0f, 0.0f,
		                            GLfloat(parseWidth), GLfloat(parseHeight),
						            Vector2f(GLfloat(parseOffsetX), GLfloat(parseOffsetY) ) ) );
	weaponCollisionBoxes.at(i).setX(position.x, handlerAnimation->getAnimationDirection());
    weaponCollisionBoxes.at(i).setY(position.y);
  }
}

void Sprite::movePosXWithSpeed()
{
  characterMovement.playerMoveInX = false || characterMovement.playerMoveInX;
  characterMovement.playerMoveInXInCurrentFrame = false;
  countX++;

  if ( countX > delayMovementSprite.at(getCurrentState()).x )
  {
    countX = 0;
    handlerAnimation->changeDirectionY( getSpeedY() );

    if ( Camera::getInstance()->isCameraLimit( getSpeedX()) )
    { 
      characterMovement.playerMoveInX = false;
      characterMovement.playerMoveInXInCurrentFrame = false;
	  setSpeedX(0.0f);
	  int animationDirection = getHandlerAnimation()->getAnimationDirection();
	  GLfloat correctPosition = 0.0f;

	  switch( animationDirection )
	  {
	    case SpriteData::RIGHT:
		{
		  correctPosition = Collider::getInstance()->getLevelLength() - spriteCollisionBox->getWidth();
          position.x = correctPosition - spriteCollisionBox->getOffset().x;
		  break;
		}
	    case SpriteData::LEFT:
	    {
		  correctPosition = -spriteCollisionBox->getX();
		  setNormalPositionX( correctPosition );
          break;
        }
	  }

      getCollisionBox()->setX( getPosX() + getCollisionBox()->getOffsetXBasedOnDirection(animationDirection), 
		                       animationDirection );
      return;
    }

	bool canMove = collisionHandler->checkPositionWithinLevelLength(*spriteCollisionBox, directionsMove, 
		                             speed, handlerAnimation->getAnimationDirection()); 

    if ( handlerAnimation->getAnimationDirection() == SpriteData::RIGHT )
    {
      if ( canMove )
      {
        if ( !directionsMove.canMoveXRight || getSpeedX() == 0.0f)
        {
          return;
        }

        characterMovement.playerMoveInX = true;
        characterMovement.playerMoveInXInCurrentFrame = true;

        rigidBody->applyNaturalPhysicForces(GamePhysics::X, &speed.x, &speed.y, 
                                            getCurrentState(), handlerAnimation->getAnimationDirection(),
											getPreviousState());

        collisionHandler->checkTileCollisionX(*getCollisionBox(), &speed.x, 
                                     handlerAnimation->getAnimationDirection(), directionsMove);
        collisionHandler->checkStateCollisionXAxis(*this);
        isOnGround = collisionHandler->onTheGround(*getCollisionBox());

		for(std::string::size_type i = 0; i < weaponCollisionBoxes.size(); i++)
	    {
	      weaponCollisionBoxes.at(i).setX( position.x, handlerAnimation->getAnimationDirection() );
	    }
        return;
      }
    }

    else if ( canMove )
    {
      if ( !directionsMove.canMoveXLeft || getSpeedX() == 0.0f )
      {
        return;
      }

      rigidBody->applyNaturalPhysicForces(GamePhysics::X, &speed.x, &speed.y, 
                                          getCurrentState(), handlerAnimation->getAnimationDirection(),
										  getPreviousState());

      characterMovement.playerMoveInX = true;
      characterMovement.playerMoveInXInCurrentFrame = true;

      collisionHandler->checkTileCollisionX(*getCollisionBox(), &speed.x,
                                     handlerAnimation->getAnimationDirection(), directionsMove);
      collisionHandler->checkStateCollisionXAxis(*this);
      isOnGround = collisionHandler->onTheGround(*getCollisionBox());

	  for(std::string::size_type i = 0; i < weaponCollisionBoxes.size(); i++)
	  {
		weaponCollisionBoxes.at(i).setX( position.x + (width - weaponCollisionBoxes.at(i).getOffset().x) - weaponCollisionBoxes.at(i).getWidth(), 
	                                     handlerAnimation->getAnimationDirection() );
	  }
	  return;
	}

    characterMovement.playerMoveInX = false;
    speed.x = 0.0f;
  }
}

void Sprite::movePosYWithSpeed()
{
  characterMovement.playerMoveInY = false || characterMovement.playerMoveInY;
  characterMovement.playerMoveInYInCurrentFrame = false;
  countY++;

  if ( countY > delayMovementSprite.at(getCurrentState()).y )
  {
    countY = 0;
    if( getBoxY() + getBoxHeight() <= 880.0f )
    {
      handlerAnimation->changeDirectionY( getSpeedY() );
      
      if ( !getPlayerDirectionYBasedInDirection() )
      {
        return;
      }

      rigidBody->applyNaturalPhysicForces(GamePhysics::Y, &speed.x, &speed.y, 
                                          getCurrentState(), handlerAnimation->getAnimationDirection(),
										  getPreviousState());

      characterMovement.playerMoveInY = true;
      characterMovement.playerMoveInYInCurrentFrame = true;


      collisionHandler->checkTileCollisionY(*getCollisionBox(), &speed.y,
                                     handlerAnimation->getDirectionY(), directionsMove);
	  
      spriteCollisionBox->setBoxYBasedOnSpeed(spriteCollisionBox->getY() + getSpeedY());
	  position.y = spriteCollisionBox->getY() - spriteCollisionBox->getOffset().y;

	  isOnGround = collisionHandler->onTheGround(*getCollisionBox());     
      collisionHandler->checkStateCollisionPlayer(*this);
	  
	  for(std::string::size_type i = 0; i < weaponCollisionBoxes.size(); i++)
	  {
	    weaponCollisionBoxes.at(i).setY( position.y );
	  }

      return;
    }

    speed.y = 0.0f;
    characterMovement.playerMoveInX = false;
    characterMovement.playerMoveInY = false;
  }
}

bool Sprite::getPlayerMoveBasedInDirection()
{
  if ( handlerAnimation->getAnimationDirection() == SpriteData::RIGHT)
  {
    return directionsMove.canMoveXRight;
  }
  return directionsMove.canMoveXLeft;
}

bool Sprite::getPlayerDirectionYBasedInDirection()
{
  if ( handlerAnimation->getDirectionY() == SpriteData::UP )
  {
    return directionsMove.canMoveYUp;
  }
  return directionsMove.canMoveYDown;
}

void Sprite::setSpeedX(GLfloat speedX)
{
  if ( !getPlayerMoveBasedInDirection() )
  {
    speed.x = 0.0f;
    return;
  }

  speed.x = speedX;
}

void Sprite::setSpeedY(GLfloat speedY)
{
  if ( getCurrentState() == GameCoreStates::FAST_ATTACK )
  {
    if ( getPreviousState() == GameCoreStates::JUMPING )
    {
      speedY = -4.0f;
	  rigidBody->getMaxSpeed().at(getCurrentState()).y = speedY;
    }

    else
    {
      speedY = 0.0f;
      rigidBody->getMaxSpeed().at(getCurrentState()).y = speedY;	  
    }
  }

  speed.y = speedY;
}

void Sprite::setConstantSpeedX(int constant)
{
  int axisDirection = handlerAnimation->returnAnimationDirectionAxisValue();
  GLfloat momentumValue = 8.0f;

  if ( constant < 0 )
  {
    speed.x *= constant;
	if ( isPlayerOnTheAir() )
	{
	  momentumValue = 4.0f;
	}
	speed.x = rigidBody->getMomentumForce(momentumValue, speed.x, axisDirection);
  }
}

void Sprite::changeCurrentFrame(int frame)
{
  handlerAnimation->setCurrentFrame(frame);
}

void Sprite::changePreviousPlayerState(int stateID)
{
  playerStateManager->changePreviousState( GameCoreStates::SpriteState(stateID) );
}

void Sprite::checkAttackCollisions()
{
//  collisionHandler->checkAttackCollisions(weaponCollisionBoxes.at(getPreviousState()));
}

bool Sprite::isPlayerOnTheAir()
{
  if ( getCurrentState() != GameCoreStates::JUMPING && 
       getCurrentState() != GameCoreStates::DOUBLE_JUMP && 
       getCurrentState() != GameCoreStates::FALLING && 
       !(getPreviousState() == GameCoreStates::JUMPING && getCurrentState() == GameCoreStates::FAST_ATTACK) )
  {
    return false;
  }
  return true;
}

void Sprite::drawTexture()
{
  GLfloat x = getBoxX();
  if( x < 0 )
  {
    x = 0;
  }

  //GameRender::drawFullTexture(textureBox, Vector2f(x, getBoxY()), getBoxWidth(), getBoxHeight());

 
  int currentState = getCurrentState();

  if ( currentState == GameCoreStates::DOUBLE_JUMP )
  {
    currentState = GameCoreStates::JUMPING;
  }

  if ( getCurrentState() == GameCoreStates::FAST_ATTACK )
  {
	int attackState = getPreviousState();
	/*GameRender::drawFullTexture(textureBox, 
		Vector2f(weaponCollisionBoxes.at(attackState).getX(), weaponCollisionBoxes.at(attackState).getY()),
	                            weaponCollisionBoxes.at(attackState).getWidth(), weaponCollisionBoxes.at(attackState).getHeight());*/
    currentState = ( GameCoreStates::FAST_ATTACK - 1 ) + getPreviousState();
  }

  if ( getCurrentState() == GameCoreStates::FALLING )
  {
    currentState = 8;
  }

  GameRender::drawSpriteTexture(texture, position,  handlerAnimation->getCurrentFrame(), width, height,  
                                handlerAnimation->getAnimationDirection(), currentState );
}