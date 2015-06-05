#pragma once
#include "gameData.h"
#include "game.h"


/**
 * \fn	string GameModeToString(Mode mode);
 *
 * \brief	Converts GameMode Enum to String.
 *
 * 
 * \param	mode	Enum to be converted.
 *
 * \return	String representation of the Enum.
 */
FASADA_DLL(string GameModeToString(Mode mode));

/**
 * \fn	string GetGameState(string playerID);
 *
 * \brief	Gets game state.
 * 
 * \param	playerID	Identifier for the player.
 *
 * \return	The game state as String.
 */
FASADA_DLL(string GetGameState(string playerID));

/**
 * \fn	GameData ConnectPlayer();
 *
 * \brief	Adds player to the game, and generates his ships.
 *
 * \return	GameData class object, with custom game info.
 */
FASADA_DLL(GameData ConnectPlayer());

/**
 * \fn	ShotResponse Shoot(string playerID, int pos_i, int pos_j);
 *
 * \brief	Executes shot, and checks whether it has been successful and whether it changed the GameState.
 *
 *
 * \param	playerID	Identifier for the player shooting.
 * \param	pos_i   	The row position.
 * \param	pos_j   	The column position.
 *
 * \return	ShotResponse class object, with custom shot info.
 */
FASADA_DLL(ShotResponse Shoot(string playerID, int pos_i, int pos_j));

/**
 * \fn	UpdateResponse Update(string playerID);
 *
 * \brief	Gets updated info about current game for inactive player. If game is finished, it is restarted so that new one can be started!
 *
 * 
 * \param	playerID	Identifier for which player to get info.
 *
 * \return	An UpdateResponse object, with custom game info.
 */
FASADA_DLL(UpdateResponse Update(string playerID));