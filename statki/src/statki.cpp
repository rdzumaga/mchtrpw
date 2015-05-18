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
	//playerA = playerB = activePlayer = NULL;
	attacked = attacker = NULL;
	gameState = IDLE;
}

std::deque<Position*> Game::addPlayer(std::string id){
	if (gameState == ONGOING || gameState == FINISHED){
		std::deque<Position*> empty;
		return empty;
	}

	if (attacker == NULL){
		attacker = new Player(id, true);
		gameState = WAITING;
		return attacker->getShipsPos();
	}
	else if (attacked == NULL){
		attacked=new Player(id, false);
		gameState = ONGOING;
		return attacked->getShipsPos();
	}
}


Player* Game::getPlayer(std::string playerId){
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

	return attackSuccesful;
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

Info* Game::getInfo(std::string playerId){
	Player * player = getPlayer(playerId);
	Info * gameInfo = new Info(player, gameState);
	return gameInfo;
}


//-----------------------Player-------------------------

//dummy constructor for avoiding null exceptions
Player::Player(){
	IP = "dummy";
	sustainedDamage = false;
	activeFlag = false;
}
Player::Player(std::string id, bool isFirstPlayer){
	IP = id;
	sustainedDamage = false;
	//remainingShipUnits = 5 + 4 + 4 + 3 + 3 + 3 + 2 + 2 + 2 + 2;
	remainingShipUnits = 5;
	activeFlag = isFirstPlayer;
}

void Player::toggleActive(){
	activeFlag = !activeFlag;
}
std::string Player::getId(){
	return IP;
}

std::deque<Position*> Player::getShipsPos(){
	std::deque<Position*> answer;
	if (ships.empty())
		placeShipsRandomly();
	
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
void Player::setActive(bool active){
	activeFlag = active;
}*/

bool Player::isActive(){
	return activeFlag;
}

bool Player::underAttack(int i, int j){
	sustainedDamage = false;
	board.shootField(i, j);
	Attack * attack = new Attack(new Position(i, j), sustainedDamage);
	receivedAttacks.push(attack);
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

Attack* Player::getLastAttack(){
	Attack* attack = NULL;
	if (!receivedAttacks.empty()){
		attack = receivedAttacks.front();
		receivedAttacks.pop();
	}
	return attack;
	
}
//-----------------------Ship-------------------------
Ship::Ship(Player* owner, int length, Orientation or, int i, int j){
	this->owner = owner;
	this->length = length;
	remainingSegements = length;
	this->orientation = or;
	pos = Position(i, j);

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
Attack::Attack(Position* pos, bool succcessful){
	this->pos = pos;
	this->successful = succcessful;
}



//-------------------------------Info --------------------------------
Info::Info(Player* player, Mode gameMode){
	this->gameMode = gameMode;
	this->playerIsUnderAttack = !player->isActive();
	this->lastAttack = player->getLastAttack();
}




//--------------------------------

STATKI_DLL( int getNumber() ) {
	return 1234;
}


