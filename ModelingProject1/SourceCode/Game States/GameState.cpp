
#include "GameState.h"

GameState::GameState(GameRender *gR, GameCore *gC, GameInput *gI, MainStates::GameStates stateName)
{
  gameCore = gC;
  gameRender = gR; 
  gameInput = gI;
  nameState = stateName;
}