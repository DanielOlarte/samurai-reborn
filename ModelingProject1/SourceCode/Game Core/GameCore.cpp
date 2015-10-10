
#include "GameCore.h"

GameCore::GameCore(void)
{
  configuration = new GameConfiguration();
  saves = new GameSaves();
  screen = new GameScreen();
  sound = new GameSound();
  camera = Camera::getInstance();
  collider = Collider::getInstance();
  isRunning = true;
}

GameCore::~GameCore(void)
{
  delete configuration;
  delete saves;
  delete screen;
  delete sound;
  delete camera;
  delete collider;
  playersList.clear();
  enemiesList.clear();
  playersInitialized.clear();
}

bool GameCore::initializeGameCore()
{	
  sound->initSound();
    
  if( screen->initializeScreen())
  {
   camera->initCamera(&playersList);
   return true;
  }
    
  return true;
}

bool GameCore::cleanUpGameCore()
{
  collider->cleanUpResources();
  sound->closeAll();

  TTF_Quit();
  SDL_Quit();

  return true;
}

void GameCore::resetCamera(GLfloat level)
{
  camera->resetCamera(level);
}

void GameCore::addPlayerToGame(Characters::Player *player, SpriteData::IDSprites id, std::string filename, 
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
                std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
                std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  playersList.push_back( player );
  playersList.at( playersList.size() - 1 ).initializeCharacter(id, filename, 
                                           pos, initialFrame, maxFrame, returnFrame,
                                           widthSprite, heightSprite, framerateAnimations,
                                           delayMovement);
}

void GameCore::addEnemyToGame(Characters::Enemy *enemy, SpriteData::IDSprites id, std::string filename,
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement)
{
  enemiesList.push_back( enemy );
  enemiesList.back().initializeCharacter(id, filename, pos, initialFrame, maxFrame, returnFrame,
                                         widthSprite, heightSprite, framerateAnimations,
                                         delayMovement);
}

void GameCore::initializeSpriteCollisionBoxPlayer(SpriteData::IDSprites id, float width, float height, GLfloat offsetX, GLfloat offsetY)
{
  for (std::string::size_type i = 0; i < playersList.size(); i++)
  {
    if ( playersList.at(i).getCharacterID() == id )
    {
      playersList.at(i).initializeSpriteCollisionBox(width, height, offsetX, offsetY);
    }
  }
}

void GameCore::initializeWeaponCollisionBoxes(SpriteData::IDSprites id, std::string filename)
{
  for (std::string::size_type i = 0; i < playersList.size(); i++)
  {
    if ( playersList.at(i).getCharacterID() == id )
    {
      playersList.at(i).initializeWeaponCollisionBoxes(filename);
    }
  }
}

/*void GameCore::initializeSpriteCollisionBoxEnemy(SpriteData::IDSprites id, float width, float height, GLfloat offsetX, GLfloat offsetY)
{
  for (std::string::size_type i = 0; i < enemiesList.size(); i++){
	if ( enemiesList.at(i).getCharacterID() == id)
	{
      enemiesList.at(i).initializeSpriteCollisionBox(width, height, offsetX, offsetY);
	}
  }
}*/

void GameCore::initializeRigidBodyVectors(SpriteData::IDSprites id, std::vector< Vector2f > maxSpeed)
{
  for (std::string::size_type i = 0; i < playersList.size(); i++)
  {
    if ( playersList.at(i).getCharacterID() == id )
    {
      playersList.at(i).initializeRigidBodyVectors(maxSpeed);
    }
  } 
}

void GameCore::setIDNumberOfPlayer(SpriteData::IDSprites id, int idPlayer)
{
  for (std::string::size_type i = 0; i < playersList.size(); i++)
  {
    if ( playersList.at(i).getCharacterID() == id )
    {
      playersList.at(i).setIDNumberOfPlayer(idPlayer);
    }
  }   
}

void GameCore::initializeTextureFaceState(std::string filename, int idPlayer)
{
  playersList.at(idPlayer).getPlayerStats()->initializeFaceStates(filename, idPlayer);
}