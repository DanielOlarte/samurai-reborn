#pragma once

#include "GameConfiguration.h"
#include "GameSaves.h"
#include "GameScreen.h"
#include "GameSound.h"

#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"

#include "Vector.h"

#include <MenuStructs.h>

class GameCore
{
  public:
   GameCore(void);
   ~GameCore(void);

   bool initializeGameCore();
   bool cleanUpGameCore();

   void initializePlayers();

   GameSound* getGameSound() { return sound; };

   Camera* getCamera() { return camera; };
   void resetCamera(GLfloat level);

   GameScreen* getGameScreen() { return screen; };

   boost::ptr_vector< Characters::Player >& getPlayersList() { return playersList; }
   boost::ptr_vector< Characters::Enemy >& getEnemyList() { return enemiesList; }

   void addPlayerToGame(Characters::Player* player, SpriteData::IDSprites id, std::string filename, Vector2f pos, 
	            int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement);
   void addEnemyToGame(Characters::Enemy* enemy, SpriteData::IDSprites id, std::string filename,
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement);

   void initializeSpriteCollisionBoxPlayer(SpriteData::IDSprites id, float width, float height, GLfloat offsetX, GLfloat offsetY);
   void initializeWeaponCollisionBoxes(SpriteData::IDSprites id, std::string filename);
   void initializeSpriteCollisionBoxEnemy(SpriteData::IDSprites id, float width, float height, GLfloat offsetX, GLfloat offsetY);
   void initializeRigidBodyVectors(SpriteData::IDSprites id, std::vector< Vector2f > maxSpeed);
   void setIDNumberOfPlayer(SpriteData::IDSprites id, int idPlayer);
   void initializeTextureFaceState(std::string filename, int idPlayer);

   bool getIsRunning() { return isRunning; }
   void setIsRunning(bool running) { isRunning = running; };

   int getCurrentGameMode() { return currentGameMode; }
   void setCurrentGameMode(int mode) { currentGameMode = mode; }

   void pushBackPlayerToInitialize(Image::PlayersInitialize initialize) { playersInitialized.push_back(initialize); }
   std::vector< Image::PlayersInitialize > getPlayersToInitialize() { return playersInitialized; }
   void clearPlayerToInitialize() { playersInitialized.clear(); }

   Image::MenuEndData getMenuEndData() { return menuEndData; }
   void setMenuEndData(Image::MenuEndData menuEnd) { menuEndData = menuEnd; }
    
  private:
   GameConfiguration* configuration;
   GameSaves* saves;
   GameScreen* screen;
   GameSound* sound;
   Camera* camera;
   Collider* collider;

   boost::ptr_vector< Characters::Player > playersList;
   boost::ptr_vector< Characters::Enemy > enemiesList;
   std::vector< Image::PlayersInitialize > playersInitialized;
   Image::MenuEndData menuEndData;
   bool isRunning;
   int currentGameMode;
};

