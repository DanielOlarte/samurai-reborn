#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Pathfinding.h"
/*
enum AIStates
{
	STATE_PATROL,
	STATE_CHASE,	
	STATE_RESET,
};
*/
enum Direction
{
	RIGHT,
	LEFT,
};

namespace AISystem
{
  class AI
  {
    public:
     AI();
     virtual ~AI();

	 //state Management
	 void selectAction(Characters::Enemy* enemy);
	 
	 //Patrol state
	 void doPatrol(Characters::Enemy* enemy, int maxDistX, int minDistX, Direction movDir);

	 //Chase state
     void searchPath(Characters::Player* player, Characters::Enemy* enemy);	 

	 //Reset state
	 void resetToPatrolZone(Characters::Enemy* enemy, int MaxDistX, int minDistX, Direction movDir);

    private: 
     Pathfinding pathfinding;
  };
}

