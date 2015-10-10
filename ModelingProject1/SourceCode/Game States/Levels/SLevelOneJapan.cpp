
#include "SLevelOneJapan.h"

#include "PandaP1.h"
#include "MeerkatP2.h"
#include "JapaneseMonkey.h"
#include "LoadingScreen.h"
#include <MenuStructs.h>

SLevelOneJapan::SLevelOneJapan(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(70);

  setHasEnded(MainStates::STATE_LEVELONEJAPAN);
  setProperty(MainStates::IN_GAME);
}

SLevelOneJapan::~SLevelOneJapan(void)
{
}

void SLevelOneJapan::init()
{
  LoadingScreen load("LevelOneSectionOne");
  load.updateValues(0);

  initializePlayers();
	
  load.updateValues(50);

  initializeLevel();
		
  load.updateValues(75);

  GameSound::getInstance()->loadSound(0, 1, 1);
  GameSound::getInstance()->loadSound(0, 1, 0);
  GameSound::getInstance()->downVolume(0, 0.5);
  
  gameCore->resetCamera(11200.0f);

  Collider::getInstance()->setLevelLength(11200);
  Collider::getInstance()->setGameMode(gameCore->getCurrentGameMode());

  inGameMenu = new Image::MenuSelection();
  inGameMenu->setNewIdGameState(MainStates::STATE_LEVELONEJAPAN);
	
  load.updateValues(100);
}

void SLevelOneJapan::resume()
{
  timer->unpause();
  setHasEnded(MainStates::STATE_LEVELONEJAPAN);
  inGameMenu->setNewIdGameState(MainStates::STATE_LEVELONEJAPAN);

  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {
	gameCore->getPlayersList().at(i).getCharacterSprite()->getHandlerAnimation()->unpauseAnimation();
  }
}

void SLevelOneJapan::handleEvents()
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

void SLevelOneJapan::logic()
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
	
	if ( gameCore->getPlayersList().at(i).getCharacterSprite()->getCurrentState() != GameCoreStates::STILL )
	{
	  Collider::getInstance()->checkCollisionsObjects(gameCore->getPlayersList().at(i), japanLevel->getReferenceTilemapList().at(2));
	}

	gameCore->getPlayersList().at(i).updateStats();
    if ( !gameCore->getPlayersList().at(i).isAlive() )
    {
      setHasEnded(MainStates::STATE_MENUSELECTIONPLAYER);
    }
  }

  gameCore->getCamera()->updateCamera();

  japanLevel->scrollContinuousBackgroundLayers();
  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {	  
	if ( gameCore->getPlayersList().at(i).getCharacterSprite()->getPlayerMoveInXCurrentFrame() )
	{
	  japanLevel->checkLayersSpeed( gameCore->getCamera()->getCameraSpeed() );
	  japanLevel->checkTilemapsSpeed( gameCore->getCamera()->getCameraSpeed() );
	  japanLevel->scrollBackgroundLayers();
	  japanLevel->scrollTilemap();
	  break;
	}
  }
  gameCore->getCamera()->setCameraSpeed(0.0f);
}

void SLevelOneJapan::render()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	
  
  japanLevel->drawLevelMap();

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

void SLevelOneJapan::cleanUp()
{
  delete japanLevel;
  delete inGameMenu;
  gameCore->getPlayersList().clear();
  gameCore->getEnemyList().clear();
}

void SLevelOneJapan::initializePlayers()
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
  maxSpeedPanda.push_back( Vector2f(0.0f, -34.0f) );
  maxSpeedPanda.push_back( Vector2f(18.0f, 0.0f) );
  maxSpeedPanda.push_back( Vector2f(0.0f, -29.0f) );
  maxSpeedPanda.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedPanda.push_back( Vector2f(0.0f, 0.0f)  );
  
  std::vector< Vector2f > maxSpeedMeerkat;
  maxSpeedMeerkat.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedMeerkat.push_back( Vector2f(12.0f, 0.0f) );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, -37.0f) );
  maxSpeedMeerkat.push_back( Vector2f(20.0f, 0.0f) );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, -32.0f) );
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
                             Vector2f(50.0f, 246.0f), 0, maxFrameVectorPanda, returnFrameVector,
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
                             Vector2f(0.0f, 271.0f), 0, maxFrameVector, returnFrameVector,
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

void SLevelOneJapan::initializeLevel()
{
  std::string commonPath = "Resources/Levels/Level One Japan/Section One/";
  japanLevel = new Level(LEVELONEJAPAN);
  japanLevel->loadTMXTileMapFile("LevelOneSectionOne", commonPath);

  japanLevel->addLayerToList(commonPath + "SkyBackground.png", 1280.f, 720.f, Vector2f(0.0f, 0.0f), 0.0f, false, false);
  japanLevel->addLayerToList(commonPath + "Clouds.png", 2400.f, 720.f, Vector2f(0.1f, 0.0f), 0.1f, true, true);
  japanLevel->addLayerToList(commonPath + "Mountains0.png", 2400.f, 720.f, Vector2f(1.0f, 0.0f), 0.2f, true, false);
  japanLevel->addLayerToList(commonPath + "Mountains1.png", 2400.f, 720.f, Vector2f(1.0f, 0.0f), 0.4f, true, false);
}

void SLevelOneJapan::handleChangeOfState(int idState)
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
