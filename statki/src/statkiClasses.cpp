#include "statkiClasses.h"
  

//=======================================================================
//=							Position										
//=======================================================================

int Position::get_i(){
	return i;
}

int Position::get_j(){
	return j;
}

//=======================================================================
//=							Attack										
//=======================================================================
Attack::Attack(Position* pos, bool succcessful){
	this->pos = pos;
	this->successful = succcessful;
}


//=======================================================================
//=							Info										
//=======================================================================
Info::Info(Player* player, Mode gameMode){
	this->gameMode = gameMode;
	this->playerIsUnderAttack = !player->isActive();
	this->receivedAttacks = player->getReceivedAttacks();
}

//=======================================================================
//=							Field										
//=======================================================================
Field::Field(){
	ship = NULL;
}
void Field::attach(ShipPtr ship){
	this->ship = ship;
	int temp = 0;
}

void Field::notify(){
	if (ship != NULL)
		ship->update();
}

bool Field::isEmpty(){
	return ship == NULL;
}

void Field::detachShip(){
	if (ship)
		ship = NULL;
}

//=======================================================================
//=							Ship										
//=======================================================================

Ship::Ship(Player* owner, int length, Orientation or, int i, int j){
	this->owner = owner;
	this->length = length;
	remainingSegements = length;
	this->orientation = or;
	pos = Position(i, j);
}

void Ship::update(){
	remainingSegements--;
	notify();
}

void Ship::notify(){
	owner->update();
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
		answer.push_back(new Position(y, x));
	}
	return answer;
}

//=======================================================================
//=							Board										
//=======================================================================

void Board::shootField(int i, int j){
	fields[i][j].notify();
}

bool Board::canPlaceShip(int i, int j, int length, int dx, int dy){
	//check if all fields starting from (i,j) are empty
	for (int l = 0; l < length; l++){
		Field  field = fields[i][j];
		if (!field.isEmpty())
			return false;
		//check for neighbors
		if (!fields[i + 1][j].isEmpty() || !fields[i][j + 1].isEmpty())
			return false;
		if (i>0)
			if (!fields[i - 1][j].isEmpty())
				return false;
		if (j > 0)
			if (!fields[i][j - 1].isEmpty())
				return false;
		i += dy;
		j += dx;
	}
	return true;
}

void Board::placeShip(ShipPtr ship){
	std::deque<Position*> shipPos = ship->getPositions();
	for (int k = 0; k < shipPos.size(); k++){
		fields[shipPos[k]->get_i()][shipPos[k]->get_j()].attach(ship);
	}
}

void Board::reset(){
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			fields[i][j].detachShip();
		}
	}
}

std::deque<Position> Board::getAvailableFields(int length, Ship::Orientation or){
	int iOffset, jOffset;
	int dx, dy;
	iOffset = jOffset = dx=dy=0;
	if (or == Ship::Orientation::HORIZONTAL){
		jOffset = length - 1;
		dx = 1;
	}
	else {
		iOffset = length - 1;
		dy = 1;
	}

	std::deque<Position> availableFieldsPos;
	for (int i = 0; i < N - iOffset; ++i){
		for (int j = 0; j < N - jOffset; ++j){
			if (fields[i][j].isEmpty())
				if (canPlaceShip(i, j, length,dx,dy))
					availableFieldsPos.push_back(Position(i, j));				
		}
	}
	return availableFieldsPos;
}

//=======================================================================
//=							Player										
//=======================================================================

Player::Player(){
	ID = "dummy";
	sustainedDamage = false;
	activeFlag = false;
}

Player::Player(std::string & id, bool isFirstPlayer){
	ID = id;
	sustainedDamage = false;
	remainingShipUnits = 5 + 4 + 4 + 3 + 3 + 3 + 2 + 2 + 2 + 2;
	activeFlag = isFirstPlayer;
}

std::deque<Position*> Player::getShipsPos(){
	std::deque<Position*> answer;
	if (ships.empty())
		placeShipsRandomly();
	
	ShipPtr shipTemp;
	for (int i = 0; i < ships.size(); i++){
		shipTemp = ships[i];
		std::deque<Position*> shipPositions = shipTemp->getPositions();
		for (int j = 0; j < shipPositions.size(); j++)
			answer.push_back(shipPositions.at(j));
	}
	return answer;
}

void Player::placeShipsRandomly(){
	//initialize random seed
	srand(time(NULL));

	ShipPtr ship;
	for (int k = 0; k < shipsNr; k++){
		int length = statkiLen[k];
		ship = placeShipRandomly(length);
		if (ship != NULL)
			ships.push_back(ship);
	}
}

ShipPtr Player::placeShipRandomly(int length){
	Ship::Orientation or = statkiOrientation[rand() % 2];
	std::deque<Position> availableFieldsPos = board.getAvailableFields(length, or);

	if (availableFieldsPos.size() == 0)
		startPlacementAgain();
	
	Position randomField = availableFieldsPos[rand() % availableFieldsPos.size()];
	ShipPtr ship = std::make_shared<Ship>(Ship(this, length, or, randomField.get_i(), randomField.get_j()));
	board.placeShip(ship);
	return ship;
}

void Player::startPlacementAgain(){
	ships.clear();
	board.reset();
	placeShipsRandomly();
}
bool Player::isActive(){
	return activeFlag;
}

bool Player::underAttack(int i, int j){
	sustainedDamage = false;
	board.shootField(i, j);
	receivedAttacks.push(new Attack(new Position(i, j), sustainedDamage));
	return sustainedDamage;
}

std::queue<Attack *> Player::getReceivedAttacks(){
	return receivedAttacks;
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

std::string Player::getId(){
	return ID;
}

void Player::toggleActive(){
	activeFlag = !activeFlag;
}




