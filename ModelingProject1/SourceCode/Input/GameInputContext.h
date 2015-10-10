#pragma once

#include <list>
#include <map>

#include "RawInputConstants.h"
#include "PlayerSpriteStates.h"

namespace InputMapping
{
  struct Key
  {
    bool isPressed;
    bool isReleased;
    bool wasPreviouslyPressed;
    RawInputButton button;

    Key(RawInputButton buttonValue, bool pressed, bool released, bool previously);
    Key();
  };

  class GameInputContext
  {
    public:
     GameInputContext(const std::string filename);
     ~GameInputContext(void);
     
     std::list<Key>* getKeysList() { return &keysList; }

	 std::map<RawInputButton, GameCoreStates::SpriteState>* getStateMap() { return &stateMap; }
	 std::map<RawInputButton, GameCoreStates::Action>* getActionMap() { return &actionMap; }

     bool mapButtonToAction(RawInputButton button, GameCoreStates::Action& outActiveAction) const;
     bool mapButtonToState(RawInputButton button, GameCoreStates::SpriteState& outActiveState) const;

    private:
     std::map<RawInputButton, GameCoreStates::Action> actionMap;
     std::map<RawInputButton, GameCoreStates::SpriteState> stateMap;
     std::list<Key> keysList;
  };
}

