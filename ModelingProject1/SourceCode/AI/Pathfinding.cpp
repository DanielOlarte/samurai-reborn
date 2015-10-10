
#include "Pathfinding.h"
#include <algorithm>
#include "PlayerStateManager.h"

AISystem::Pathfinding::Pathfinding(void)
{
  level = new LevelGraph(6400,720);
  coordinates = Vector2i(0, 0);
}

AISystem::Pathfinding::~Pathfinding(void)
{	
  openNodes.clear();
  closedNodes.clear();
  delete level;
}
    
void AISystem::Pathfinding::goToPlayer(Characters::Enemy* enemy, Characters::Player* player)
{							//only function to be called
  int xPlayer = (int)player->getCharacterSprite()->getPosX();
  int yPlayer = (int)player->getCharacterSprite()->getPosY();
  int xEnemy = (int)enemy->getCharacterSprite()->getPosX();
  int yEnemy = (int)enemy->getCharacterSprite()->getPosY();

  if(xEnemy > xPlayer)
  {
    direction = SpriteData::LEFT;
  }
  else
  {
    direction = SpriteData::RIGHT;
  }

  openNodes.clear();																//clear previous iterations
  closedNodes.clear();	

  int cost = 0;																		//----
  int heuristic = 0;																//set the initial values of the path
  int scoreFunction = 0;															//

  setVariablesByPosition(xPlayer,yPlayer,cost,heuristic,scoreFunction);			    //----

  PathNode* playerNode = level->getNodeByPosition(xPlayer, yPlayer);				//pointer to starting node
  PathNode* enemyNode( level->getNodeByPosition(xEnemy, yEnemy) );					//pointer to goal node

  openNodes.push_back(playerNode);												    //algoritm starts with current node open
  PathNode* currentNode;															//node to be used on the iterations

  while(!openNodes.empty())                                                         //and while the path its not a dead end
  {														
    currentNode = openNodes.back();												    //assign the front of the min heap to currentNode,
    if(currentNode->getID() == enemyNode->getID())                                  //if we are there
    {								 
      if(abs(xPlayer - xEnemy) < 10)                                                //and the distance is to short
      {												
        return;																        //do nothing
      }																		        //otherwise
      calculatePath(enemyNode,playerNode);									        //calculate the valid path
      goToPosition(enemy);													        //then follow the player with AI function
      return;
    }
    else                                                                            //if not
    {																			
      PathNode* currentClosedNode = currentNode;
      closedNodes.push_back(currentClosedNode);								        //--the current node is now 
            
      openNodes.pop_back();													        //--closed
      std::pop_heap(openNodes.begin(),openNodes.end(), HeapCompare());			    //(rearrange heap after pop)

      for(unsigned i = 0; i < currentNode->getAdjacentNodes()->size(); i++)         //and for its adjacent nodes
      {		
        std::vector<int>* vect = currentNode->getAdjacentNodes();
        PathNode* adjacentNode = level->getNodeByID( currentNode->getAdjacentNodes()->at(i) );

        if(!searchNode(adjacentNode,openNodes))                                                //if it isnt on the open list
        {							
          if(!searchNode(adjacentNode,closedNodes))                                            //and it isnt in the closed list
          {						
            //and if it isnt a colision then
            adjacentNode->cost = 1;										                       //asign costs
            adjacentNode->heuristic = (GLfloat)abs(enemyNode->getID() - currentNode->getID()); //and heuristics
            adjacentNode->scoreFunction = (GLfloat)currentNode->scoreFunction + 
                                                 adjacentNode->cost +
                                                 adjacentNode->heuristic;		               //and finally calculate the score function
            openNodes.push_back(adjacentNode);							                       //add it to openlist

            std::push_heap(openNodes.begin(),openNodes.end(), HeapCompare());                  //rearrange heap
                        //end if colision
          }
        }
      }
    }
  }
}

void AISystem::Pathfinding::goToPosition(Characters::Enemy* enemy)
{
  //temporal code
  enemy->getCharacterSprite()->changeStateSprite(WALKING_STATE);	
  if(enemy->getCharacterSprite()->getHandlerAnimation()->getAnimationDirection() != direction)
  {
    enemy->getCharacterSprite()->getHandlerAnimation()->changeAnimationDirection(direction);
    enemy->getCharacterSprite()->setConstantSpeedX(-1);
  }		
  enemy->walk();
    //temporal code, here is suposed to go the decision function
}

bool AISystem::Pathfinding::searchNode(AISystem::PathNode* node, std::vector<AISystem::PathNode*> vector)
{
  if(vector.size() > 0)
  {
    for(unsigned i = 0; i < vector.size(); i++)
    {	
      if(vector[i]->getID() == node->getID())
      {
        return true;
      }
    }		
  }
  return false;
}

void AISystem::Pathfinding::calculatePath(AISystem::PathNode* node,AISystem::PathNode* goalNode)
{
  path.clear();

  PathNode* pathNode;
  pathNode = node;
  pathNode->scoreFunction = FLT_MAX;
  path.push_back(pathNode);

  while(pathNode->getID()!=goalNode->getID())
  {
    GLfloat tentativeMinScore = FLT_MAX;
    PathNode* tempPathNode;
    for(unsigned i = 0; i < pathNode->getAdjacentNodes()->size(); i++)
    {
      PathNode* adjacentNode = level->getNodeByID( pathNode->getAdjacentNodes()->at(i) );
      if(adjacentNode->scoreFunction < tentativeMinScore)
      {
        tentativeMinScore = adjacentNode->scoreFunction;
        tempPathNode = adjacentNode;
      }
      adjacentNode->scoreFunction=FLT_MAX;
    }

    path.push_back(tempPathNode);
    pathNode = tempPathNode;
  }

  path.push_back(pathNode);
}

void AISystem::Pathfinding::setVariablesByPosition(int x, int y, int cost, int heuristic, int score)
{
  level->getNodeByPosition(x,y)->cost = (GLfloat)cost;
  level->getNodeByPosition(x,y)->heuristic = (GLfloat)heuristic;
  level->getNodeByPosition(x,y)->scoreFunction = (GLfloat)score;
}