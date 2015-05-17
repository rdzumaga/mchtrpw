/**
 * \file statki.cpp
 * \brief the C++ file with statki library
 */
#include "statki.hpp"

#include <cstdlib>     /* srand, rand */
#include <ctime>
#include <iostream>

//-----------------------Game-------------------------

Game::Game(){
	playerA = playerB = activePlayer = NULL;
	state.mode = IDLE;
}

std::deque<Position*> Game::addPlayer(std::string id){
	if (state.mode == ONGOING || state.mode == FINISHED){
		std::deque<Position*> empty;
		return empty;
	}

	if (playerA == NULL){
		playerA = new Player(id, true);
		state.mode = WAITING;
		state.attackingPlayerId = id;
		activePlayer = playerA;
		return playerA->getShipsPos();
	}
	else if (playerB == NULL){
		playerB=new Player(id, false);
		state.mode = ONGOING;
		state.attackedPlayerId = id;
		return playerB->getShipsPos();

	}
}

bool Game::begin(){
	if (playerA != NULL && playerB != NULL){
		state.mode = ONGOING;
		state.attackingPlayerId = playerA->getId();
		return true;
	}
	return false;
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

int Game::shoot(int i, int j, std::string attackerId){
	Player* attacker = getPlayer(attackerId);
	if (activePlayer == attacker){
		Player* attacked = getPlayer(state.attackedPlayerId);
		bool attackSuccesful = attacked->underAttack(i, j);
		Attack* attack = new Attack(new Position(i, j), attackSuccesful, attackerId);
		if (attacked->hasLost())
			finish();

		if (!attackSuccesful)
			switchActivePlayer();

		state.attacks.push(attack);
		//state.attacks.push(attack);//for queue
		return attackSuccesful;
	}
	return ERROR;
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
	while (!state.attacks.empty()){
		state.attacks.pop();
	}
	//std::deque<Attack*> empty;
	//state.attacks.swap(empty);
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
	if (ships.empty()){
		placeShipsRandomly();
	}
	
	//TODO: calculate ships positions and return them
	int temp = ships.size();
	Ship* shipTemp;
	for (int i = 0; i < ships.size(); i++){
		shipTemp = ships[i];
		std::deque<Position*> shipPositions = shipTemp->getPositions();
		for (int j = 0; j < shipPositions.size(); j++)
			answer.push_back(shipPositions.at(j));
	}

	return answer;
}

void Player::placeShipsRandomly(){
	static int playerNr = 0;
	/* initialize random seed: */
	//srand(time(NULL));
	srand(5000);

	Ship* ship;
	for (int k = 0; k < shipsNr; k++){
		int length = statkiLen[k];
		Ship::Orientation or = statkiOrientation[rand() % 2];
		ship = placeShipRandomly(length, or);
		if (ship != NULL)
			ships.push_back(ship);
		//TO DO remove printing
		else
			std::cout << "Error: new random ship is null!\n";
	}
	playerNr++;
}

Ship* Player::placeShipRandomly(int length, Ship::Orientation or){
	//set the initial scope for placing ships for i and j index - initally it is set to the full lenght of the board
	int iScope = N;
	int jScope = N;

	//variables for calculating the position of all tiles belonging to one ship
	int dx = 0;
	int dy = 0;

	if (or == Ship::Orientation::HORIZONTAL){
		jScope = N - length ;
		dx = 1;
	}
	else {
		iScope = N - length ;
		dy = 1;
	}

	int i = rand() % iScope;
	int j = rand() % jScope;
	
	int failsafe = 0;
	while (!board.canPlaceShip(i, j, length, dx, dy)){
		i = rand() % iScope;
		j = rand() % jScope;
		failsafe++;
		if (failsafe > 1000)
			return NULL;
	}
	Ship* ship = new Ship(this, length, or, i, j);
	board.placeShip(ship);
	return ship;
}

/*
void Player::placeShipsRandomly0(){
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
	
	playerNr++;
}*/

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
/*
Ship::Ship(Player* owner){
	this->owner = owner;
	this->pos = pos;
}*/


std::deque<Position*> Ship::getPositions(){
	std::deque<Position*> answer;
	answer.push_back(&pos);
	int dx = 1;
	int dy = 1;
	if (orientation == HORIZONTAL)
		dy = 0;
	else
		dx = 0;

	int x = pos.get_j();
	int y = pos.get_i();
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

void Board::shootField(int i, int j){
	Field * f = &fields[i][j];
	f->notify();
	//fields[i][j].notify();
}


bool Board::canPlaceShip(int i, int j, int length, int dx, int dy){
	//check if all fields starting from (i,j) are empty
	for (int l = 0; l < length; l++){
		Field * field = &fields[i][j];
		if (!field->isEmpty())
			return false;
		//check for neighbours
		if (!fields[i + 1][j].isEmpty() || !fields[i - 1][j].isEmpty() || !fields[i][j + 1].isEmpty() || !fields[i][j - 1].isEmpty())
			return false;
		i += dy;
		j += dx;
	}
	return true;
}

void Board::placeShip(Ship* ship){
	std::deque<Position*> shipPos = ship->getPositions();
	for (int k = 0; k < shipPos.size(); k++){
		fields[shipPos[k]->get_i()][shipPos[k]->get_j()].attach(ship);
	}

}
//-------------------------Position------------------

int Position::get_i(){
	return i;
}

int Position::get_j(){
	return j;
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

bool Field::isEmpty(){
	return ship == NULL;
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


