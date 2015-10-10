#include "PathNode.h"

AISystem::PathNode::PathNode(int ID, int newX, int newY)
{
  this->ID = ID;
  cost = FLT_MAX;
  scoreFunction = FLT_MAX;
  heuristic = FLT_MAX;
  coordinates = Vector2i(newX, newY);
}

AISystem::PathNode::~PathNode(void)
{
  adjacentID.clear();
}

void AISystem::PathNode::addAdjacentNode(int ID)
{
  adjacentID.push_back(ID);
}