/**
* \file game.h
* \brief Game class file  */

#ifndef GAME_H
#define GAME_H

#include"statki.hpp"


#ifdef FASADA_EXPORTS
//Workaround for Windows DLL library exports
#define FASADA_DLL(X) __declspec(dllexport)X
#else
//Workaround for Unix Shared Library exports
#define FASADA_DLL(X) X
#endif


/**
* \class    Game
*
* \brief    Main game class
*/
class FASADA_DLL(Game){
public:
	///singleton method
	static Game& getInstance();

	///destructor
	~Game();

	/** \brief Add player method.
	* \param id the string used to identify player during communication with server
	* \return list of ships' positions
	*
	* This method adds one of two possible players to the game and return a list of randomly chosen ships' positions
	*/
	std::deque<Position*> addPlayer(std::string & id);

	/** \brief get update about the game.
	* \param id the string used to identify player during communication with server.
	* \return Info object containing details about the state of the game
	*/
	Info getInfo(std::string playerId);

	/** \brief Shoot opponent's filed.
	* \param i number of targeted row (value from 0 to 9).
	* \param j number of targeted column (value from 0 to 9).
	* \return 1 if there was a ship placed on the targeted field, 0 otherwise.
	*/
	int shoot(int i, int j);

	///method reseting game to its initial state
	void reset();

private:
	Player* attacker;
	Player* attacked;
	Mode gameState;

	void switchActivePlayer();
	Player* getPlayer(std::string & playerId);
	void finish();
	Game();
	Game(Game const &) = delete;
	void operator=(Game const &) = delete;
};


#endif