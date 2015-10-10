
#include "AI.h"

AISystem::AI::AI(void)
{
}

AISystem::AI::~AI(void)
{
}

void AISystem::AI::selectAction(Characters::Enemy* enemy)
{
	if(enemy->getState() == STATE_PATROL)
	{

	}

	else if(enemy->getState() == STATE_CHASE)
	{

	}

	else if(enemy->getState() == STATE_RESET)
	{

	}
}

void AISystem::AI::searchPath(Characters::Player* player, Characters::Enemy* enemy)
{
  pathfinding.goToPlayer(enemy, player);
}

void AISystem::AI::doPatrol(Characters::Enemy* enemy, int maxDistX, int minDistX, Direction movDir)
{
	int currentPosX = (int)enemy->getCharacterSprite()->getPosX();

	if(movDir == RIGHT)
	{
		enemy->walk();

		if(currentPosX == maxDistX)
		{
			movDir = LEFT;
		}
	}

	if(movDir == LEFT)
	{
		enemy->walk();

		if( currentPosX == minDistX )
		{
			movDir = RIGHT;
		}
	}
}

void AISystem::AI::resetToPatrolZone(Characters::Enemy* enemy, int MaxDistX, int minDistX, Direction movDir)
{
	int currentPosX = (int)enemy->getCharacterSprite()->getPosX();

	if(currentPosX > MaxDistX)
	{
		enemy->run();	
	}

	else if(currentPosX < minDistX)
	{
		enemy->run();
	}

}


