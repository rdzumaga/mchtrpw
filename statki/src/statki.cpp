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

std::deque<Position*> Player::getShipsPos(){
	if (ships.empty())
		int x = 1;
	//	placeShipsRandomly();
	
	std::deque<Position*> answer;
	int r, t;
	r = t = 0;
	//for (int i = 0; i < ships.size(); i++){
		//r++;
		//std::deque<Position*> shipPositions = ships.at(i)->getPositions();
		//for (int j = 0; j < shipPositions.size(); j++)
			//t++;
			//answer.push_back(shipPositions[j]);
	//}


	return answer;
}

void Player::placeShipsRandomly(){
	//temporarily, positions are hardcoded
	static int playerNr = 0;

	//for each ship
	Ship* ship;
	for (int i = 0; i < shipsNr; i++){
		int length = statkiLen[i];
		Ship::Orientation or = statkiOrientation[i];
		int s_i = statkiPos[i][0];
		int s_j = statkiPos[i][1];
		ship = new Ship(this, length, or, s_i, s_j);

		int dx = 1;
		int dy = -1;
		if (or == Ship::HORIZONTAL)
			dy = 0;
		else
			dx = 0;

		for (int l = 0; l < length; l++){
			board.fields[s_i][s_j].attach(ship);
			s_i += dx;
			s_j += dy;
		}
		ships.push_back(ship);
	}
	//for each field on the board
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			;
		}
	}
	/*

	for (int i = 0; i < N; i++){		
		for (int j = 0; j < N; j++){
			int length = 0;
			if (!sameShip)
				ship = new Ship(this, Position(i, j));
			if (boardA[i][j]){
				length++;
			}
			else{
				if (length)
					ship = new Ship(this, Position(i, j), length, Ship::HORIZONTAL);
				length = 0;
			}
				sameShip = false;
		}
	}*/


	playerNr++;
}
//-----------------------Ship-------------------------
Ship::Ship(Player* owner, int length, Orientation or, int i, int j){
	this->owner = owner;
	this->length = length;
	remainingSegements = length;
	this->orientation = or;
	pos = Position(i, j);

}
Ship::Ship(Player* owner){
	//this->owner = owner;
	//this->pos = pos;
}







//-----------------------Board-------------------------

void Board::populateField(int i, int j, bool shipFlag){
	//if (shipFlag){
		;//fields[i][j]
	//}
	
}









//-----------------------Ship-------------------------

void Field::attach(Ship* ship){
	this->ship = ship;
}









//--------------------------------

STATKI_DLL( int getNumber() ) {
	return 1234;
}


