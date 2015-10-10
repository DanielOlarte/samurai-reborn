#pragma once

#include "PathNode.h"
#include <vector>

#include "Vector.h"

namespace AISystem
{
  typedef std::vector<PathNode> Container;

  class LevelGraph
  {
    public:
     LevelGraph(int levelLength, int levelHeight);
     ~LevelGraph(void);

     void initGraph();

     PathNode* getNodeByPosition(int xPosition, int yPosition);
     PathNode* getNodeByID(int ID);

     int getNodeXIndex(PathNode node);

     void addNode(std::vector<int>* parentNodes, int x, int y);

    private:
     std::vector<Container> nodes;
     Vector2i mapDivision;
     Vector2i levelMeasures;
     int idGenerator;
  };
}