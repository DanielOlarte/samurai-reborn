#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <vector>

#include "Vector.h"

namespace AISystem
{
  class PathNode
  {
    public:
     PathNode(int ID, int x, int y);
     ~PathNode(void);

     int getID() { return ID; }
     void setID(unsigned newID) { ID = newID; }
    
     void addAdjacentNode(int ID);

     std::vector<int>* getAdjacentNodes() { return &adjacentID; }

     void setCoordinates(int newX, int newY) { coordinates = Vector2i(newX, newY); }

     int getXCoord() { return coordinates.x; }
     int getYCoord() { return coordinates.y; }

     GLfloat cost;
     GLfloat heuristic;
     GLfloat scoreFunction;

    private:
     Vector2i coordinates;
     int ID;
     std::vector<int> adjacentID;
  };
}


