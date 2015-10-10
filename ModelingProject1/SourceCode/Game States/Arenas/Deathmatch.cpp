
#include "Deathmatch.h"

#include "PandaP1.h"
#include "MeerkatP2.h"
#include "JapaneseMonkey.h"
#include "LoadingScreen.h"

#include <MenuStructs.h>

Deathmatch::Deathmatch(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(70);

  setHasEnded(MainStates::STATE_ARENA_MODE);
  setProperty(MainStates::IN_GAME);
}

Deathmatch::~Deathmatch(void)
{
}

void Deathmatch::init()
{
  LoadingScreen load("CaveArenaMode");
  load.updateValues(0);

  initializePlayers();

  load.updateValues(50);

  initializeLevel();

  load.updateValues(75);

  gameCore->resetCamera(1280.0f);

  Collider::getInstance()->setLevelLength(1280);
  Collider::getInstance()->setGameMode(gameCore->getCurrentGameMode());

  inGameMenu = new Image::MenuSelection();
  inGameMenu->setNewIdGameState(MainStates::STATE_ARENA_MODE);
  
  load.updateValues(100);
}

void Deathmatch::resume()
{
  timer->unpause();
  setHasEnded(MainStates::STATE_ARENA_MODE);
  inGameMenu->setNewIdGameState(MainStates::STATE_ARENA_MODE);

  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {
	gameCore->getPlayersList().at(i).getCharacterSprite()->getHandlerAnimation()->unpauseAnimation();
  }
}

void Deathmatch::handleEvents()
{
  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {	
    gameCore->getPlayersList().at(i).getInputMapper()->clearCurrentMappedInput(
            GameCoreStates::SpriteState( gameCore->getPlayersList().at(i).getCharacterSprite()->getCurrentState() ) );
  }

  bool isRunning = gameInput->handleWindowEvents();
  gameCore->setIsRunning( isRunning );

  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {	
    gameInput->handleKeyEvents( gameCore->getPlayersList().at(i).getInputMapper(), 
		                        gameCore->getPlayersList().at(i).getController() );
  }
}

void Deathmatch::logic()
{
  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {	
    gameCore->getPlayersList().at(i).getInputMapper()->dispatchInput( gameCore->getPlayersList().at(i),
	                           *gameCore->getPlayersList().at(i).getController()->getListKeys(), *inGameMenu );

    if ( inGameMenu->getNewIdGameState() != getNameState() )
    {
	  handleChangeOfState(inGameMenu->getNewIdGameState());
	  setHasEnded( inGameMenu->getNewIdGameState() );
	  return;
	}
  }

  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {	
    gameCore->getPlayersList().at(i).executeAction();
	if ( gameCore->getPlayersList().at(i).getCharacterSprite()->getCurrentState() == GameCoreStates::FAST_ATTACK )
	{
	  Collider::getInstance()->checkAttackCollisions(gameCore->getEnemyList(), gameCore->getPlayersList(), i );
	}

	gameCore->getPlayersList().at(i).updateStats();
    if ( !gameCore->getPlayersList().at(i).isAlive() )
    {
	  gameCore->setMenuEndData( Image::MenuEndData(gameCore->getPlayersList().at(i).getCharacterID()) );
      setHasEnded(MainStates::STATE_ARENA_WINNER);
    }
  }

  deathmatchLevel->scrollContinuousBackgroundLayers();
  
  if ( gameCore->getPlayersList().at(0).getCharacterSprite()->getPlayerMoveInXCurrentFrame() )
  {
    deathmatchLevel->checkLayersSpeed( gameCore->getCamera()->getCameraSpeed() );
    deathmatchLevel->checkTilemapsSpeed( gameCore->getCamera()->getCameraSpeed() );
    deathmatchLevel->scrollBackgroundLayers();
    deathmatchLevel->scrollTilemap();
  }
  gameCore->getCamera()->setCameraSpeed(0.0f);
}

void Deathmatch::render()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	
  
  deathmatchLevel->drawLevelMap();

  glPushMatrix();
    
    gameCore->getCamera()->renderCamera();
      
    for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
    {
      gameCore->getPlayersList().at(i).draw();
    }

    for (std::string::size_type i = 0; i < gameCore->getEnemyList().size(); i++)
    {
      gameCore->getEnemyList().at(i).draw();
    }
    
  glPopMatrix();

  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {
    gameCore->getPlayersList().at(i).drawUIStats();
    gameCore->getPlayersList().at(i).drawScore();
  }

  SDL_GL_SwapBuffers();
}

void Deathmatch::cleanUp()
{
  delete deathmatchLevel;
  delete inGameMenu;
  gameCore->getPlayersList().clear();
  gameCore->getEnemyList().clear();
}

void Deathmatch::initializePlayers()
{
  std::vector<Image::PlayersInitialize> playersToInitialize = gameCore->getPlayersToInitialize();

  if ( playersToInitialize.size() > 1 )
  {
    if ( playersToInitialize.at(0).characterID > playersToInitialize.at(1).characterID )
	{
	  std::swap(playersToInitialize.at(0), playersToInitialize.at(1));
	}
  }

  std::vector< Vector2f > maxSpeedPanda;
  maxSpeedPanda.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedPanda.push_back( Vector2f(10.0f, 0.0f) );
  maxSpeedPanda.push_back( Vector2f(0.0f, -38.0f) );
  maxSpeedPanda.push_back( Vector2f(18.0f, 0.0f) );
  maxSpeedPanda.push_back( Vector2f(0.0f, -35.0f) );
  maxSpeedPanda.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedPanda.push_back( Vector2f(0.0f, 0.0f)  );
  
  std::vector< Vector2f > maxSpeedMeerkat;
  maxSpeedMeerkat.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedMeerkat.push_back( Vector2f(12.0f, 0.0f) );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, -40.0f) );
  maxSpeedMeerkat.push_back( Vector2f(20.0f, 0.0f) );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, -35.0f) );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, 0.0f)  );

  std::vector < int > maxFrameVector;
  maxFrameVector.push_back( 0 );
  maxFrameVector.push_back( 8 );
  maxFrameVector.push_back( 5 );
  maxFrameVector.push_back( 6 );
  maxFrameVector.push_back( 5 );
  maxFrameVector.push_back( 4 );
  maxFrameVector.push_back( 2 );
  maxFrameVector.push_back( 6 );

  std::vector < int > maxFrameVectorPanda;
  maxFrameVectorPanda.push_back( 0 );
  maxFrameVectorPanda.push_back( 8 );
  maxFrameVectorPanda.push_back( 5 );
  maxFrameVectorPanda.push_back( 8 );
  maxFrameVectorPanda.push_back( 4 );
  maxFrameVectorPanda.push_back( 5 );
  maxFrameVectorPanda.push_back( 2 );
  maxFrameVectorPanda.push_back( 8 );

  std::vector < int > returnFrameVector;
  returnFrameVector.push_back( 0 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 0 );
  returnFrameVector.push_back( 0 );
  returnFrameVector.push_back( 1 );

  std::vector < Vector2f > delayMovementVector;
  delayMovementVector.push_back( Vector2f(0.0f, 0.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 0.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 4.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 0.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 4.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 4.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 4.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 0.0f) );

  std::vector < int > framerateAnimationsVector;
  framerateAnimationsVector.push_back( 0 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 70 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 100 );

  for (std::string::size_type i = 0; i < gameCore->getPlayersToInitialize().size(); i++)
  {
	switch(playersToInitialize.at(i).characterID)
    {
      case SpriteData::PANDA:
      {
        gameCore->addPlayerToGame( new Characters::PandaP1(), SpriteData::PANDA, 
			                 "Resources/Characters/Players/Panda - SpriteSheet.png", 
                             Vector2f(50.0f, 54.0f), 0, maxFrameVectorPanda, returnFrameVector,
                             280.0f, 218.0f, framerateAnimationsVector, delayMovementVector);
        gameCore->initializeSpriteCollisionBoxPlayer(SpriteData::PANDA, 85.0f, 160.0f, 97.0f, 42.0f);
		gameCore->initializeWeaponCollisionBoxes(SpriteData::PANDA, "Resources/Characters/Players/WeaponCollisionBoxesPanda.txt");
		gameCore->initializeRigidBodyVectors(SpriteData::PANDA, maxSpeedPanda);
		gameCore->setIDNumberOfPlayer(SpriteData::PANDA, (int)i);
		gameCore->initializeTextureFaceState("Resources/UI/PandaFacesStates.png", i);
        break;
      }
      case SpriteData::MEERKAT:
      {
        gameCore->addPlayerToGame( new Characters::MeerkatP2(), SpriteData::MEERKAT, 
			                 "Resources/Characters/Players/Meerkat - SpriteSheet.png", 
                             Vector2f(10.0f, 527.0f), 0, maxFrameVector, returnFrameVector,
                             340.0f, 187.0f, framerateAnimationsVector, delayMovementVector);
        gameCore->initializeSpriteCollisionBoxPlayer(SpriteData::MEERKAT, 32.0f, 135.0f, 153.0f, 42.0f);
		gameCore->initializeWeaponCollisionBoxes(SpriteData::MEERKAT, "Resources/Characters/Players/WeaponCollisionBoxesMeerkat.txt");
		gameCore->initializeRigidBodyVectors(SpriteData::MEERKAT, maxSpeedMeerkat);
		gameCore->setIDNumberOfPlayer(SpriteData::MEERKAT, (int)i);
	    gameCore->initializeTextureFaceState("Resources/UI/MeerkatFacesStates.png", i);
		break;
      }
    }
	
	gameCore->getPlayersList().at(i).setController(GameInput::initializeControllerData(getNameState(), playersToInitialize.at(i).controllerID));
    gameCore->getPlayersList().at(i).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                    *gameCore->getPlayersList().at(i).getController(), 
										playersToInitialize.at(i).controllerID));
	gameCore->getPlayersList().at(i).getController()->setPlayerID(playersToInitialize.at(i).controllerID);
	gameCore->getPlayersList().at(i).getScore()->initializeTextAndFonts("", (int)i, "Resources/UI/Numbers.png");
  }

  maxSpeedPanda.clear();
  maxSpeedMeerkat.clear();
  maxFrameVector.clear();
  returnFrameVector.clear();
  delayMovementVector.clear();
  framerateAnimationsVector.clear();
}

void Deathmatch::initializeLevel()
{
  std::string commonPath = "Resources/Arenas/Cave/";
  deathmatchLevel = new Level(LEVELONEJAPAN);
  deathmatchLevel->loadTMXTileMapFile("CaveArenaMode", commonPath);
}

void Deathmatch::handleChangeOfState(int idState)
{
  switch(idState)
  {
    case MainStates::STATE_PAUSE:
	{
	  timer->pause();

      for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
      {
	    gameCore->getPlayersList().at(i).getCharacterSprite()->getHandlerAnimation()->pauseAnimation();
	  }
	  break;
	}
  }
}