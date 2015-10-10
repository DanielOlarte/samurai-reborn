#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>

#include "GameRender.h"

#include "Animation.h"
#include "PlayerStateManager.h"

#include "RigidBody.h"

#include "CollisionBox.h"
#include "CollisionStructs.h"

#include "Vector.h"

#include "SpriteDataConstants.h"

class Collider;

class Sprite
{
  public:
   virtual ~Sprite();

   virtual void changeStateSprite( GameCoreStates::PlayerState* newState, int keyPreviouslyPressed = 0, 
	                               std::list<InputMapping::Key> keys = std::list<InputMapping::Key>(),
								   InputMapping::Controller& controller = InputMapping::Controller() ) = 0;

   void initializeSpriteCollisionBox(float width, float height, GLfloat offsetX, GLfloat offsetY);
   void initializeWeaponCollisionBoxes(std::string filename);

   SpriteData::IDSprites getID() { return ID; }

   GLfloat getPosX() { return position.x; }
   void setNormalPositionX(GLfloat x) { position.x += x; }
   void movePosXWithSpeed();

   GLfloat getPosY() { return position.y; }
   void setNormalPositionY(GLfloat y) { position.y += y; }
   void movePosYWithSpeed();

   bool getPlayerMoveBasedInDirection();
   bool getPlayerDirectionYBasedInDirection();

   bool getPlayerMoveInX() { return characterMovement.playerMoveInX; }
   void setPlayerMoveInX(bool moveX) { characterMovement.setMoveX(moveX); }

   bool getPlayerMoveInY() { return characterMovement.playerMoveInY; }
   void setPlayerMoveInY(bool moveY) { characterMovement.setMoveY(moveY); }

   void setPlayerCanMoveYUp(bool moveYUp) { directionsMove.setCanMoveUp(moveYUp); }
   void setPlayerCanMoveYDown(bool moveYDown) { directionsMove.setCanMoveDown(moveYDown); }

   GameCoreStates::PlayerStateManager* getPlayerStateManager() { return playerStateManager; }

   CollisionSystem::CharacterMovement getCharacterMovement() { return characterMovement; }

   CollisionSystem::DirectionsMove getDirectionsMove() { return directionsMove; }

   GLfloat getSpeedX() { return speed.x; }

   void setSpeedX(GLfloat speedX);
   void setConstantSpeedX(int constant);

   GLfloat getSpeedY() { return speed.y; }
   void setSpeedY(GLfloat speedY);

   GLuint getTexture() { return texture; }

   GLfloat getWidthTexture(){ return widthTexture;}
   GLfloat getWidth() { return width; }
   GLfloat getHeight() { return height; }

   Animation*getHandlerAnimation() { return handlerAnimation; }
   void changeCurrentFrame(int frame);

   int getCurrentState() { return playerStateManager->getCurrentState(); }

   void changePreviousPlayerState(int stateID);
   
   int getPreviousState() { return playerStateManager->getPreviousState(); }

   Collider* getCollisionHandler() { return collisionHandler; }
   CollisionSystem::CollisionBox* getCollisionBox() { return spriteCollisionBox; }
   CollisionSystem::CollisionBox* getWeaponCollisionBox() { return &weaponCollisionBoxes.at(getPreviousState()); }

   void checkAttackCollisions();

   GLfloat getBoxX() { return spriteCollisionBox->getX(); }
   GLfloat getBoxY() { return spriteCollisionBox->getY(); }
   GLfloat getBoxWidth() { return spriteCollisionBox->getWidth(); }
   GLfloat getBoxHeight() { return spriteCollisionBox->getHeight(); }

   bool isPlayerOnTheAir();
   bool getIsOnGround() { return isOnGround; }

   bool getPlayerMoveInXCurrentFrame() { return characterMovement.playerMoveInXInCurrentFrame; }
   void setPlayerMoveInXCurrentFrame(bool moveX) { characterMovement.setMoveXFrame(moveX); }
   bool getPlayerMoveInYCurrentFrame() { return characterMovement.playerMoveInYInCurrentFrame; }

   GamePhysics::RigidBody& getRigidBody() { return *rigidBody; }

   void drawTexture();

  protected:
   Sprite(SpriteData::IDSprites id, std::string filename, Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
	      std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
          std::vector< Vector2f> delayMovement);

   SpriteData::IDSprites ID;
   GLuint texture, textureBox;
   Animation* handlerAnimation;
   GameCoreStates::PlayerStateManager* playerStateManager;
   Collider* collisionHandler;
   CollisionSystem::CollisionBox* spriteCollisionBox;
   boost::ptr_vector<CollisionSystem::CollisionBox> weaponCollisionBoxes;
   CollisionSystem::DirectionsMove directionsMove;
   CollisionSystem::CharacterMovement characterMovement;
   GamePhysics::RigidBody* rigidBody;
    
   Vector2f position;
   Vector2f speed;
   std::vector< Vector2f > delayMovementSprite;
   GLfloat width, height, widthTexture, heightTexture;
   int countX, countY;
   bool isOnGround;
};

