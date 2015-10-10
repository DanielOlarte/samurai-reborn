#pragma once

#include "RawInputConstants.h"
#include "PlayerSpriteStates.h"
#include "GameInputContext.h"

#include <Controller.h>
#include <MenuSelection.h>

#include <GameInputStructs.h>

#include <map>
#include <set>
#include <list>
#include <string>
#include <vector>

namespace Characters
{
  class Player;
}

namespace InputMapping 
{
  typedef void (*inputCallback)(MappedInput& inputs, Characters::Player& player, std::list<Key> keys, Image::MenuSelection& menu);
  
  class GameInputContext;
  
  class GameInputMapper
  {
    public:
     GameInputMapper(std::string filename);
     ~GameInputMapper(void);

	 void clearCurrentMappedInput(GameCoreStates::SpriteState activeState = GameCoreStates::STILL);
     void addCallback(inputCallback callback, int priorityInMultimap);
     void dispatchInput(Characters::Player& player, std::list<Key>& keys = std::list<Key>(), 
		                Image::MenuSelection& menu = Image::MenuSelection()) const;

     void pushContext(const std::string& name);
     void popContext();

     void processNewInput(Controller& controller);

     std::list<Key> getListKeys() const; 

	 std::map<RawInputButton, GameCoreStates::SpriteState> getStateMap() const;
	 std::map<RawInputButton, GameCoreStates::Action> getActionMap() const;

     void pushBackStateOnMappedInput(GameCoreStates::SpriteState newState);
	 void pushBackActionOnMappedInput(GameCoreStates::Action newAction);

    private:
     std::map<std::string, GameInputContext*> inputContexts;
     std::list<GameInputContext*> activeContexts;
     std::multimap<int, inputCallback> callbackTable;
     MappedInput currentMappedInput;

     bool mapButtonToAction(RawInputButton button, GameCoreStates::Action& action) const;
     bool mapButtonToState(RawInputButton button, GameCoreStates::SpriteState& state) const;
  };
}

