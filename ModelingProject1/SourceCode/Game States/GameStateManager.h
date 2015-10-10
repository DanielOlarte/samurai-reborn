#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "GameState.h"

class GameStateManager
{
  public:
   GameStateManager(void);
   ~GameStateManager(void);
    
   void pushState( GameState* gameState );
   void popState();
   void changeState( GameState* gameState ) ;
   void changeCurrentState(GameRender* gR, GameCore* gC, GameInput* gI);

   void init();
   void startTimer();
   void delayTimer();
   void resume();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();

   bool checkChangeOfState(int currentStateProperty, int newStateProperty);

  private:
   boost::ptr_vector< GameState > statesStack;
   MainStates::GameStates currentState;
   int currentID;

   int checkIfCurrentStateHasEnd();
   void popBackMenuInGameState(int currentState);
};

