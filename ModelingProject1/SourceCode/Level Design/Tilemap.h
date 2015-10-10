#pragma once

#include <windows.h>
#include <GL/gl.h>

#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#include "GameRender.h"
#include "Tile.h"
#include "Tileset.h"

class Tilemap
{
  public:
   Tilemap(std::string name, int widthInTiles, int heightInTiles);
   ~Tilemap(void);

   void drawTilemap(int indexTileset);
   GLfloat transformOffsetXToIntervalValues(GLfloat offX);
   void scrollTilemap();
   bool checkScreenBoundaries();
    
   std::vector< std::vector < Tile > > getLayerMap() { return layerMap; } ;
   void setLayerMap(std::vector< std::vector < Tile > > map) { layerMap = map; };

   int getWidthLevelInTiles() { return widthLevelInTiles; }
   void setWidthLevelInTiles(int width) { widthLevelInTiles = width; }

   int getHeightLevelInTiles() { return heightLevelInTiles; }
   void setHeightLevelInTiles(int height) { heightLevelInTiles = height; }

   void setVelocityX(GLfloat velX) { speed.x = velX; }

   boost::ptr_vector< Tileset > getTilesetList() { return tilesetList; }
   void addTileset(int id, std::string name, GLfloat widthTile, GLfloat heightTile, GLfloat imageWidth, 
                   GLfloat imageHeight, int size);

  private:
   std::string nameLayer;
   std::vector< std::vector < Tile > > layerMap;
   Vector2f offset, speed;
   int widthLevelInTiles, heightLevelInTiles;
   GLfloat sizeTiles;
   boost::ptr_vector< Tileset > tilesetList;
};

