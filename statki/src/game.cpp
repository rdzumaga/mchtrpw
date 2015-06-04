
#include "game.h"

//=======================================================================
//=							Game										
//=======================================================================

Game& Game::getInstance(){
	static Game instance;
	return instance;
}
Game::Game(){
	attacked = attacker = NULL;
	gameState = IDLE;
}

void Game::reset(){
	attacked = attacker = NULL;
	gameState = IDLE;
}

std::deque<Position*> Game::addPlayer(std::string & id){
	if (attacker == NULL){
		attacker = new Player(id, true);
		gameState = WAITING;
		return attacker->getShipsPos();
	}
	else if (attacked == NULL){
		attacked = new Player(id, false);
		gameState = ONGOING;
		return attacked->getShipsPos();
	}
	std::deque<Position*> empty;
	return empty;
}

Info Game::getInfo(std::string & playerId){
	return Info(getPlayer(playerId), gameState);
}

Player* Game::getPlayer(std::string & playerId){
	if (attacker != NULL){
		if (playerId == attacker->getId())
			return attacker;
		else if (attacked != NULL)
			return attacked;
	}
	return new Player();
}

int Game::shoot(int i, int j){
	bool attackSuccesful = attacked->underAttack(i, j);
	if (attacked->hasLost())
		finish();

	if (!attackSuccesful)
		switchActivePlayer();

	return (int)attackSuccesful;
}

void Game::switchActivePlayer(){
	attacker->toggleActive();
	Player* newAttacker = attacked;
	attacked = attacker;
	attacker = newAttacker;
	attacker->toggleActive();
}

void Game::finish(){
	gameState = FINISHED;
}

Game::~Game(){
	delete attacker;
	delete attacked;
}