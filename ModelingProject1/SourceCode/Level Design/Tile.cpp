#include "Tile.h"


Tile::Tile(void)
{
  IDTileset = 0;
  ID = 0;
  hasCollision = false;
}

Tile::Tile(int idTileset, int id)
{
  IDTileset = idTileset;
  ID = id;
  hasCollision = false;
}

Tile::~Tile(void)
{
}
