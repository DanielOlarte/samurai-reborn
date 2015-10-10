#pragma once

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"
#include "GameSound.h"

#include <GameTimer.h>

#include <GameStatesData.h>

class GameState
{
  public:
   virtual void init() { };
   virtual void resume() { };
   virtual void handleEvents() { };
   virtual void logic() { };
   virtual void render() { };
   virtual void cleanUp() { };
   virtual ~GameState() { };

   MainStates::GameStates getNameState() { return nameState; }

   int checkIfStateEnd() { return hasEnded; }
   void setHasEnded(int stateHasEnded) { hasEnded = stateHasEnded; }

   int getProperty() { return propertyState; }
   void setProperty(int stateProperty) { propertyState = stateProperty; }

   void startTimer() { timer->start(); }
   void delayTimer() { timer->delay(); }

   GameTimer& getGameTimer() { return *timer; }

  private:
   int hasEnded;
   int propertyState;

  protected:
   GameState( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   GameRender* gameRender;
   GameCore* gameCore;
   GameInput* gameInput;
   GameTimer* timer;
   MainStates::GameStates nameState;
};

