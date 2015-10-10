#pragma once

#include <GameInputContext.h>
#include <RawInputConstants.h>

#include <GameInputStructs.h>

namespace InputMapping
{
  class Controller
  {
    public:
	  Controller(){};
     ~Controller();

	 int getPlayerID() { return playerID; }
	 void setPlayerID(int id) { playerID = id; }

	 int getTypeController() { return typeController; }

	 virtual bool isEnabled() { return enabled; }
	 void setIsEnabled(bool enabled) { this->enabled = enabled; }

	 std::string getFileContextList() { return filenameContext; }

	 std::list<Key>* getListKeys() { return &keys; }

	 std::map<RawInputButton, GameCoreStates::SpriteState>* getStateMap() { return &stateMap; }

	 void initializeKeys(std::list<Key> listKeys, std::map<RawInputButton, GameCoreStates::SpriteState> mapKeys,
		                 std::map<RawInputButton, GameCoreStates::Action> actionKeys);

	 void setWasPreviouslyPressedAllKeys();

	 Key& getKeyAssociatedToState(int state, int directionX = 0);

	 void setRawButtonState(Key key, MappedInput& inputs);

	 bool checkIfCanCleanStateVector(MappedInput& inputs);
	 void countAndClearStates(MappedInput& inputs);
	 int countStatesInMapper(MappedInput& inputs, int state);
	 bool verifyDoubleTappingForJumping(MappedInput& inputs, GameCoreStates::SpriteState state);
     void pushBackNewState(MappedInput& inputs, int state, int valueButton);
	 
	 virtual void parseRawInput(Key& key, MappedInput& inputs){};
	 virtual Key getKeyDirectionX(int directionX){ return Key(); }
	 virtual void updateStateKeys(MappedInput& inputs){};

    private:
	 bool mapButtonToAction(RawInputButton button, GameCoreStates::Action& out) const;
     bool mapButtonToState(RawInputButton button, GameCoreStates::SpriteState& state) const;

    protected:
	 Controller(int id);

     int playerID, typeController;
	 bool enabled;
	 std::string filenameContext;
     std::list<Key> keys;
     std::map<RawInputButton, GameCoreStates::SpriteState> stateMap;
	 std::map<RawInputButton, GameCoreStates::Action> actionMap;
  };
}

