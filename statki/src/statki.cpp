/**
 * \file statki.cpp
 * \brief the C++ file with statki library
 */
#include "statki.hpp"


//-----------------------Game-------------------------

Game::Game(){
	playerA = playerB = activePlayer = NULL;
}

bool Game::addPlayer(std::string id){
	if (state.mode == ONGOING || state.mode == FINISHED)
		return false;

	if (playerA == NULL){
		playerA = new Player(id);
		state.mode = WAITING;
		state.attackingPlayerId = id;
	}
	else if (playerB == NULL){
		playerB=new Player(id);
		state.mode = ONGOING;
		state.attackedPlayerId = id;
	}
	return true;
}

bool Game::begin(){
	if (playerA != NULL && playerB != NULL){
		state.mode = ONGOING;
		state.attackingPlayerId = playerA->getId();
		return true;
	}
	return false;
}

std::deque<Position*> Game::getShipsPos(std::string playerId){
	std::deque<Position*> temp;
	return temp;
	//return getPlayer(playerId)->getShipsPos();
}

Player* Game::getPlayer(std::string playerId){
	if (playerId == playerA->getId())
		return playerA;
	else
		return playerB;
}
//-----------------------GameState-------------------------
GameState::GameState(){
	mode = IDLE;
	attackedPlayerId = attackingPlayerId = "";

}



//-----------------------Player-------------------------

Player::Player(std::string id){
	IP = id;
	sustainedDamage = false;
}

std::string Player::getId(){
	return IP;
}


//-----------------------Ship-------------------------










//-----------------------Game-------------------------










//-----------------------Game-------------------------








//--------------------------------

STATKI_DLL( int getNumber() ) {
	return 1234;
}


