
#include <crtdbg.h>

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"

#include "GameStateManager.h"

#include "SIntro.h"
#include "SMainMenu.h"
#include "SPlayerSelection.h"
#include "SLevelOneJapan.h"
#include "SSoundOptions.h"

int main( int argc, char* args[] )
{
  GameCore Core;
  GameRender Render;
  GameInput Input;
  GameStateManager* StateManager = new GameStateManager();
    
  if( !Core.initializeGameCore() )
  {
    return 1;
  }

  StateManager->changeState( new SIntro( &Render, &Core, &Input, MainStates::STATE_INTRO ) );
  //StateManager->changeState( new SMainMenu( &Render, &Core, &Input, MainStates::STATE_MAINMENU ) );

  StateManager->init();

  while( Core.getIsRunning() )
  {
    StateManager->changeCurrentState( &Render, &Core, &Input );

	StateManager->startTimer();

    StateManager->handleEvents();
    StateManager->logic();
    StateManager->render();

    StateManager->delayTimer();
  }
  
  StateManager->cleanUp();

  delete StateManager;

  Core.cleanUpGameCore();

  return 0;
}
