#pragma once

class Tile
{
  public:
   Tile(void);
   Tile(int idTileset, int id);
   ~Tile(void);

   int getIDTileset() { return IDTileset; }
   void setIDTileset(int id) { IDTileset = id; }

   int getID() { return ID; }
   void setID(int id) { ID = id; }

   bool getHasCollision() { return hasCollision; }
   void setHasCollision(bool collision) { hasCollision = collision; }

   bool getIsWalkable() { return isWalkable; }
   void setIsWalkable(bool walkable) { isWalkable = walkable; }

  private:
   int IDTileset;
   int ID;
   bool hasCollision;
   bool isWalkable;
};

