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
		playerA = new Player(id, true);
		state.mode = WAITING;
		state.attackingPlayerId = id;
		activePlayer = playerA;
	}
	else if (playerB == NULL){
		playerB=new Player(id, false);
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
	//std::deque<Position*> temp;
	//return temp;
	return getPlayer(playerId)->getShipsPos();
}

Player* Game::getPlayer(std::string playerId){
	if (playerId == playerA->getId())
		return playerA;
	else
		return playerB;
}

GameState* Game::getGameState(){
	return &state; //maybe pop an attack from queue if sender id==attacked?
}

bool Game::shoot(int i, int j, std::string attackerId){
	Player* attacker = getPlayer(attackerId);
	Player* attacked = getPlayer(state.attackedPlayerId);
	bool attackSuccesful=attacked->underAttack(i, j);
	Attack* attack = new Attack(new Position(i, j), attackSuccesful, attackerId);
	if (attacked->hasLost())
		 finish();

	if (!attackSuccesful)
		switchActivePlayer();
	
	state.attacks.push_back(attack);
	//state.attacks.push(attack);//for queue
	return attackSuccesful;
}

void Game::switchActivePlayer(){
	Player* newAttacker = getPlayer(state.attackedPlayerId);
	state.attackedPlayerId = state.attackingPlayerId;
	state.attackingPlayerId=newAttacker->getId();
	activePlayer->setActive(false);
	activePlayer = newAttacker;
	activePlayer->setActive(true);	
	//clear the attacks queue
	//std::queue<Attack*> empty;
	std::deque<Attack*> empty;
	state.attacks.swap(empty);
}

void Game::finish(){
	state.mode = FINISHED;
}
//-----------------------GameState-------------------------
GameState::GameState(){
	mode = IDLE;
	attackedPlayerId = attackingPlayerId = "";

}



//-----------------------Player-------------------------

Player::Player(std::string id, bool isFirstPlayer){
	IP = id;
	sustainedDamage = false;
	remainingShipUnits = 5 + 4 + 4 + 3 + 3 + 3 + 2 + 2 + 2 + 2;
	activeFlag = isFirstPlayer;
}

std::string Player::getId(){
	return IP;
}

std::deque<Position*> Player::getShipsPos(){
	std::deque<Position*> answer;
	if (ships.empty())
		placeShipsRandomly();
	
	//TODO: calculate ships positions and return them

	for (int i = 0; i < ships.size(); i++){
		std::deque<Position*> shipPositions = ships.at(i)->getPositions();
		for (int j = 0; j < shipPositions.size(); j++)
			answer.push_back(shipPositions.at(j));
	}

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
		int dy = 1;
		if (or == Ship::HORIZONTAL)
			dy = 0;
		else
			dx = 0;

		for (int l = 0; l < length; l++){
			board.fields[s_i][s_j].attach(ship);
			s_i += dy;
			s_j += dx;
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

void Player::setActive(bool active){
	activeFlag = active;
}

bool Player::isActive(){
	return activeFlag;
}

bool Player::underAttack(int i, int j){
	sustainedDamage = false;
	board.shootField(i, j);
	return sustainedDamage;
}

bool Player::hasLost(){
	if (remainingShipUnits > 0)
		return false;
	return true;
}

void Player::update(){
	remainingShipUnits--;
	sustainedDamage = true;
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
	this->owner = owner;
	this->pos = pos;
}


std::deque<Position*> Ship::getPositions(){
	std::deque<Position*> answer;
	answer.push_back(&pos);
	int dx = 1;
	int dy = 1;
	if (orientation == HORIZONTAL)
		dy = 0;
	else
		dx = 0;

	int x = pos.j;
	int y = pos.i;
	for (int i = 1; i < length; i++){
		x += dx;
		y += dy;
		answer.push_back(new Position(y,x));
	}

	return answer;
}

void Ship::update(){
	remainingSegements--;
	notify();
}

void Ship::notify(){
	owner->update();
}


//-----------------------Board-------------------------

void Board::populateField(int i, int j, bool shipFlag){
	//if (shipFlag){
		;//fields[i][j]
	//}
	
}

void Board::shootField(int i, int j){
	Field * f = &fields[i][j];
	f->notify();
	//fields[i][j].notify();
}








//-----------------------Field-------------------------
Field::Field(){
	ship = NULL;
}
void Field::attach(Ship* ship){
	this->ship = ship;
	int temp = 0;
}

void Field::notify(){
	if (ship!=NULL)
		ship->update();
}

//-----------------------Attack-------------------------

Attack::Attack(Position* pos, bool successful, std::string attackerId){
	this->pos = pos;
	this->successful = successful;
	this->attackerId = attackerId;
}








//--------------------------------

STATKI_DLL( int getNumber() ) {
	return 1234;
}


