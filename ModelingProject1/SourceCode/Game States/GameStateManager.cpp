
#include "GameStateManager.h"

#include "SIntro.h"
#include "SMainMenu.h"
#include "SLevelOneJapan.h"
#include "SPlayerSelection.h"
#include "SPause.h"
#include "SSoundOptions.h"
#include "Deathmatch.h"
#include "SArenaWinner.h"
#include "SCredits.h"

GameStateManager::GameStateManager(void)
{
  currentState = MainStates::STATE_NULL;
  currentID = 0;
}

GameStateManager::~GameStateManager(void)
{
  statesStack.clear();
}

void GameStateManager::pushState(GameState* gameState)
{
  statesStack.push_back(gameState);
}

void GameStateManager::popState()
{
  statesStack.pop_back();
}

void GameStateManager::changeState(GameState* gameState)
{
  while( !statesStack.empty() )
  {
    popState();
  }

  pushState(gameState);
  currentState = gameState->getNameState();
  currentID = 0;
}

void GameStateManager::changeCurrentState(GameRender* gR, GameCore* gC, GameInput* gI)
{
  using namespace MainStates;

  int newChangeState = checkIfCurrentStateHasEnd();
  int currentGameState = statesStack.at(currentID).getNameState();
  int currentProperty = statesStack.at(currentID).getProperty();

  if ( newChangeState != currentGameState && checkChangeOfState(currentProperty, Properties[newChangeState]) )
  {
    switch(newChangeState)
    {
      case STATE_INTRO:
      {
        cleanUp();
        changeState(new SIntro( gR, gC, gI, STATE_INTRO ) );
        break;
      }
      case STATE_MAINMENU:
      {
        cleanUp();
        changeState(new SMainMenu( gR, gC, gI, STATE_MAINMENU ) );
        break;
      }
      case STATE_MENUSELECTIONPLAYER:
      {
        cleanUp();
        changeState(new SPlayerSelection( gR, gC, gI, STATE_MENUSELECTIONPLAYER ) );
        break;
      }
      case STATE_LEVELONEJAPAN:
      {
        cleanUp();
        changeState(new SLevelOneJapan( gR, gC, gI, STATE_LEVELONEJAPAN ) );
        break;
      }
	  case STATE_PAUSE:
	  {
		popBackMenuInGameState(currentGameState);
		GameSound::getInstance()->pauseSystem();
		statesStack.push_back(new SPause( gR, gC, gI, STATE_PAUSE ) );
		currentID = 1;
		currentState = statesStack.at(currentID).getNameState();
		break;
	  }
	  case STATE_SOUNDS_OPTIONS:
	  {
		cleanUp();
		statesStack.pop_back();
		statesStack.push_back(new SSoundOptions( gR, gC, gI, STATE_SOUNDS_OPTIONS ) );
		currentID = 1;
		currentState = statesStack.at(currentID).getNameState();
		break;
	  }
	  case STATE_ARENA_MODE:
      {
        cleanUp();
        changeState(new Deathmatch( gR, gC, gI, STATE_ARENA_MODE ) );
        break;
      }
	  case STATE_ARENA_WINNER:
	  {
        cleanUp();
        changeState(new SArenaWinner( gR, gC, gI, STATE_ARENA_WINNER ) );
        break;
	  }
	  case STATE_CREDITS:
	  {
	    cleanUp();
        changeState(new SCredits( gR, gC, gI, STATE_CREDITS ) );
        break;
	  }
    }

	init();
	return;
  }

  if ( newChangeState != statesStack.at(currentID).getNameState() )
  {
    if ( statesStack.at(currentID).getNameState() == STATE_PAUSE  )
    {
      statesStack.pop_back();
	  currentState = statesStack.at(0).getNameState();
	  currentID = 0;
	  resume();
    }
  }
}

void GameStateManager::init()
{
  statesStack.at(currentID).init();
}

void GameStateManager::resume()
{
  statesStack.at(currentID).resume();
}

void GameStateManager::startTimer()
{
  statesStack.at(currentID).getGameTimer().start();
}

void GameStateManager::delayTimer()
{
  statesStack.at(currentID).getGameTimer().delay();
}

void GameStateManager::handleEvents()
{
  statesStack.at(currentID).handleEvents();
}

void GameStateManager::logic()
{
  statesStack.at(currentID).logic();
}

void GameStateManager::render()
{
  statesStack.at(currentID).render();
}

void GameStateManager::cleanUp()
{
  statesStack.at(currentID).cleanUp();
}

bool GameStateManager::checkChangeOfState(int currentStateProperty, int newStateProperty)
{
  using namespace MainStates;
  
  if ( currentStateProperty == IN_GAME && newStateProperty == MENU_IN_GAME )
  {
	return true;
  }

  if ( currentStateProperty == MENU_IN_GAME && newStateProperty == MENU_IN_GAME )
  {
	return true;
  }

  if ( currentStateProperty == MENU_IN_GAME && newStateProperty == IN_GAME )
  {
	return false;
  }

  return true;
}

int GameStateManager::checkIfCurrentStateHasEnd()
{
  return statesStack.at(currentID).checkIfStateEnd();
}

void GameStateManager::popBackMenuInGameState(int currentState)
{
  if ( currentState == MainStates::STATE_SOUNDS_OPTIONS )
  {
	cleanUp();
    statesStack.pop_back();
  }
}

