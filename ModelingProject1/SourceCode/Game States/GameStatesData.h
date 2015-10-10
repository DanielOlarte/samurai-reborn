#pragma once

namespace MainStates
{
  enum GameStates 
  {
    STATE_NULL,
    STATE_INTRO, 
    STATE_MAINMENU, 
    STATE_MENUSELECTIONPLAYER,
    STATE_LEVELZEROTUTORIAL, 
    STATE_LEVELONEJAPAN,
	STATE_PAUSE,
	STATE_SOUNDS_OPTIONS,
	STATE_ARENA_MODE,
	STATE_ARENA_WINNER,
	STATE_IN_GAME,
	STATE_CREDITS,
    STATE_EXIT,
  };

  enum GameMode
  {
	LEVELS,
	ARENAS,
	MENUS,
  };

  const int Properties[13] = { 0, 0, 0, 0, 1, 1, 2, 2, 1, 0, 1, 0, 0 };

  enum PropertiesStates
  {
    NORMAL_MENU,
	IN_GAME,
	MENU_IN_GAME,
  };
}