
#include "Tilemap.h"
#include <math.h>

Tilemap::Tilemap(std::string name, int widthInTiles, int heightInTiles)
{
  nameLayer = name;
  widthLevelInTiles = widthInTiles;
  heightLevelInTiles = heightInTiles;
  offset.x = offset.y = 0.0f;
  sizeTiles = 32.f;

  layerMap.resize(heightLevelInTiles);
    
  for (int i = 0; i < heightLevelInTiles; i++)
  {
    layerMap[i].resize(widthLevelInTiles);
  }
}

Tilemap::~Tilemap(void)
{
  layerMap.clear();
}

void Tilemap::drawTilemap(int indexTileset)
{
  GLfloat offsetXTemp = offset.x;
    
  offsetXTemp = transformOffsetXToIntervalValues(offset.x);
    
  GLfloat variableSizeTile = 32.f;

  GLfloat widthTilesetImage = tilesetList.at(indexTileset).getWidthImage();
  GLfloat heightTilesetImage = tilesetList.at(indexTileset).getHeightImage();

  int widthMap = (1280 / (int)sizeTiles) + 1;
  int heigthMap = (int) ceil( 720.0f / sizeTiles );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );	
    
  glBindTexture( GL_TEXTURE_2D, tilesetList.at(indexTileset).getTexture() );

  GLfloat posXPrevious = 0.0f, posXPreviousOnTexture = 0.0f;

  for (int i = 0; i < heigthMap; i++)
  {
    int startX = (int)floor(offset.x/sizeTiles);
    posXPrevious = 0.0f;

    posXPrevious -= offsetXTemp;
    variableSizeTile = 32.f;

	if ( i == heightLevelInTiles )
	{
	  break;
	}

    for (int j = 0; j < widthMap; j++) 
    {
      if ( startX == widthLevelInTiles )
      {
        break;
      }
            
      int frameIndex = layerMap[i][startX].getID();

      if ( frameIndex == 0 )
      { 
        startX++;
        variableSizeTile = 32.f;
        posXPrevious = posXPrevious + variableSizeTile;
        continue; 
      }

      if ( j == 0 && offsetXTemp != sizeTiles)
      {
        posXPreviousOnTexture = offsetXTemp/widthTilesetImage;
        variableSizeTile -= offsetXTemp;
        posXPrevious = 0.0f;
      }

      else 
      { 
        variableSizeTile = 32.f; 
        posXPreviousOnTexture = 0.0f;
      }

      if ( j == 40 )
      {
        variableSizeTile = offsetXTemp;
      }

      frameIndex -= 1;

      const GLfloat tileX = posXPrevious;
      const GLfloat tileY = sizeTiles * i;
      posXPrevious = tileX + variableSizeTile;

      const GLfloat verts[] = {
                    tileX, tileY,
                    tileX + variableSizeTile, tileY,
                    tileX + variableSizeTile, tileY + sizeTiles,
                    tileX, tileY + sizeTiles
      };

      const GLfloat textureWidth = variableSizeTile / (GLfloat)widthTilesetImage;
      const GLfloat textureHeight = sizeTiles / (GLfloat)heightTilesetImage;
      const int numFramePerRow = (int)widthTilesetImage / (int)sizeTiles;
      const GLfloat textureX = ( (frameIndex % numFramePerRow) * sizeTiles/(GLfloat)widthTilesetImage ) 
                                    + posXPreviousOnTexture;
      const GLfloat textureY = ( frameIndex / numFramePerRow ) * textureHeight;

      const GLfloat texVerts[] = {
                    textureX, textureY,
                    textureX + textureWidth, textureY,
                    textureX + textureWidth, textureY + textureHeight,
                    textureX, textureY + textureHeight
      };
            
      glVertexPointer(2, GL_FLOAT, 0, verts);
      glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
      glDrawArrays(GL_QUADS, 0, 4);

      startX++;
    }	
  }

  glDisableClientState( GL_VERTEX_ARRAY );			
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

GLfloat Tilemap::transformOffsetXToIntervalValues(GLfloat offX)
{
  int modForTextureCoordinates = (int)sizeTiles* (int)( floor(offX/sizeTiles) );

  if (offX > sizeTiles*2 ) 
  { 
    return offX - modForTextureCoordinates; 
  }

  else if ( offX > sizeTiles && offX <= sizeTiles*2 )
  {
    return offX - sizeTiles;
  } 

  return offX;
}

void Tilemap::scrollTilemap()
{
  offset.x += speed.x;
  offset.y += speed.y;

  checkScreenBoundaries();
}

bool Tilemap::checkScreenBoundaries()
{
  if (offset.x > widthLevelInTiles*sizeTiles - 1280.f)
  {
    offset.x = widthLevelInTiles*sizeTiles - 1280.f; 
    return true;
  }

  if ( offset.x < 0 )
  {
    offset.x = 0;
    return true;
  }

  return false;
}

void Tilemap::addTileset(int id, std::string name, GLfloat widthTile, GLfloat heightTile, 
                         GLfloat imageWidth, GLfloat imageHeight, int size)
{
  tilesetList.push_back( new Tileset(id, name, widthTile, heightTile, imageWidth, imageHeight, size, GameRender::loadTexture(name)) );
}