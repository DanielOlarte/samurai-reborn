#pragma once

#include <windows.h>

#include <string>
#include <GL/gl.h>

class Tileset
{
  public:
   Tileset(int id, std::string name, GLfloat widthTile, GLfloat heightTile, GLfloat imageWidth, GLfloat imageHeight, 
           int size, GLuint tex);
   ~Tileset(void);

   GLuint getTexture() { return texture; }

   GLfloat getHeightImage() { return heightImage; }
   void setHeightImage(GLfloat height) { heightImage = height; }

   GLfloat getWidthImage() { return widthImage; }
   void setWidthImage(GLfloat width) { widthImage = width; }

   void setID(int id) { ID = id; }

   void setFilename(std::string name) { filename = name; }

   void setHeightTile(GLfloat height) { heightTile = height; }

   void setWidthTile(GLfloat width) { widthTile = width; }

   void setNumberOfTiles(int number) { numberOfTiles = number; }

   void setTexture(GLuint tex) { texture = tex; }

  private:
   std::string filename;
   GLuint texture;
   int ID;
   GLfloat heightTile, widthTile;
   GLfloat heightImage, widthImage;
   int numberOfTiles;
};

