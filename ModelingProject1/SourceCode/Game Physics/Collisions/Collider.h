#pragma once

#include "CollisionBox.h"
#include <Tilemap.h>
#include "Enemy.h"
#include "Player.h"
#include "Tile.h"

class Collider
{
  public:
   static Collider* getInstance();
   
   void addLayerTilemap(std::vector< std::vector < Tile > > layer);

   void setGameMode(int mode) { gameMode = mode; }
   
   void setLevelLength(int length) { levelLength = length; }

   void cleanUpResources();
   
   bool checkCollision(CollisionSystem::CollisionBox& A, CollisionSystem::CollisionBox& B);

   void checkTileCollisionX(CollisionSystem::CollisionBox& A, GLfloat* speedX, int directionX, 
	                        CollisionSystem::DirectionsMove& directionsMove);
   void checkTileCollisionY(CollisionSystem::CollisionBox& A, GLfloat* speedY, int directionY, 
                           CollisionSystem::DirectionsMove& directionsMove);
   int positionCollisionBoxAxisX(CollisionSystem::CollisionBox& A, int directionX, GLfloat newSpeed, int rightCondition);
   int positionCollisionBoxAxisY(CollisionSystem::CollisionBox& A, int directionY, GLfloat newSpeed, int rightCondition);

   void checkTopBoxCollision( CollisionSystem::DirectionsMove& directionsMove, int topY, int directionY, int currentPositionY );
   void checkBodyBoxCollision( CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, int directionX,
	                            int currentPositionY );
   void checkBottomBoxCollision( CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, 
                                 int directionX, int currentPositionX, int currentPositionY);
   bool checkBottomBoxMovementY( CollisionSystem::DirectionsMove& directionsMove, int newRightDirection, int currentY, int boxXtreme,
	                             bool tileIsWalkable );

   void checkStateCollisionPlayer( Sprite& playerSprite );
   void checkStateCollisionXAxis( Sprite& playerSprite );
   void checkStatePhysicsModes( Sprite& playerSprite );

   void checkAttackCollisions( boost::ptr_vector< Characters::Enemy >& enemiesList, 
                               boost::ptr_vector< Characters::Player >& playersList, 
							   int indexPlayer );

   void checkArenaCollisions( boost::ptr_vector< Characters::Player >& playersList, int indexPlayer );
   void checkEnemiesCollisions( boost::ptr_vector< Characters::Enemy >& enemiesList, CollisionSystem::CollisionBox& A );

   void checkCollisionsObjects( Characters::Player& player, Tilemap& tilemap );

   bool onTheGround(CollisionSystem::CollisionBox& A);

   bool checkPositionWithinLevelLength(CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, 
	                                   Vector2f speed, int directionX);

   int getLevelLength() { return levelLength; }

  protected:
   Collider();

  private:
   static bool instanceFlag;
   static Collider* collider;
   int levelLength;
   int gameMode;
   std::vector< std::vector< std::vector < Tile > > > layers;
   int numberOfCollisionLayers;
   bool hasObjectLayerChange;
};