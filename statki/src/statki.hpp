/**
 * \file statki.hpp
 * \brief the C++ statki library interface
 */

#ifndef STATKI_HPP
#define STATKI_HPP

#ifdef STATKI_EXPORTS
/** Workaround for Windows DLL library exports */
#define STATKI_DLL(X) __declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define STATKI_DLL(X) X
#endif

/*
Assumption:
	- Each field can have a pointer to only one ship
	- Each player has a different ID (int)
	- The game board's size is 10x10. The Fields are numbered from 0 till 9
	- A ships' position on the game board is defined by it starting position (uppermost segment or the first segment on the left side) 
	  and its orientation. So if lenght=3, orientation=horizontal and pos=(1,1), then the ship is placed on the following fields: (1,1), (1,2), (1,3)

*/

#include <deque>
#include <string>
#include <queue>
const int N = 10;
const int shipsNr = 3;

class Player;

class Field;
class Ship;
class Position;
class Attack;
class GameState;
class Game;

enum Mode { IDLE, WAITING, ONGOING, FINISHED };


class Attack{
public:
	Attack();
	Position * pos;
	bool successful;
	std::string attackerId;
};

class GameState{
public:
	GameState();
	Mode mode;
	std::string attackingPlayerId;
	std::string attackedPlayerId;
	//a queue listing attacks of the active player in one turn
	std::queue<Attack *> attacks;
};

class Game{
	//friend class GameState;
public:
	Game();
	

	bool awaitSecondPlayer();
	bool addPlayer(std::string id);
	bool begin();
	void finish();
	bool shoot(int i, int j, int attackerId);
	std::deque<Position*> getShipsPos(std::string playerId);
	
	
	
private:
	Player* activePlayer;
	Player* playerA;
	Player* playerB;
	//Mode mode;
	GameState state;

	void switchActivePlayer();
	void updateGameState();
	Player* getPlayer(std::string playerId);

};



class Position{
public:
	Position(){}
	Position(int i, int j) : i(i), j(j) {}
	int i;
	int j;
};

class Field{
public:
	Field(){}
	void attach(Ship* ship);
	void detach(Ship* ship); //unnecessary?
	void notify();
private:
	Ship* ship;
};

class Board{
public:
	Board(){}
	void shootField(int i, int j);
	void populateField(int i, int j, bool shipFlag);
	Field fields[N][N];
};

class Ship{
public:
	enum Orientation { HORIZONTAL, VERTICAL };
	Ship(Player* owner);
	Ship(Player* owner, int length, Orientation or, int i, int j);
	
	bool isSunk();
	void update();
	void attacked();
	std::deque<Position*> getPositions();
private:
	Player* owner;
	int length;
	int remainingSegements;
	Orientation orientation;
	Position pos;

	void notify();
};

class Player{
public:
	Player(std::string id);
	bool underAttack(int i, int j);
	bool hasLost();
	std::deque<Position*> getShipsPos();
	
	void update();

	bool isAttacking;
	std::string getId();
private:
	Board board;
	int remainingShips;
	std::deque<Ship*> ships;
	bool sustainedDamage;
	std::string IP;

	void placeShipsRandomly();
};



//const int statkiLen[] = { 5, 4, 4, 3, 3, 3, 2, 2, 2, 2 };
const int statkiLen[shipsNr] = { 5, 4, 3};
const int statkiPos[][2] = { 
		{0,0},
		{9.0},
		{2,0}
};

const Ship::Orientation statkiOrientation[] = {
	Ship::Orientation::HORIZONTAL,
	Ship::Orientation::HORIZONTAL,
	Ship::Orientation::VERTICAL
};
/*
const bool boardA[][N] = {
		{ 1, 1, 1, 1, 1, 0, 1,1,1,1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 0, 1, 1, 0, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 1, 1, 0, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0,0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }

};

const int boardA[][N] = {
		{1,1,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,1,1},
		{1,0,0,1,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,0,1,0,0,1},
		{0,0,0,0,0,0,1,0,0,0},
		{1,1,1,1,0,0,1,0,1,1}

};*/





















//------------------------------------------------

//! Example C++ calculation. This function return a number.
STATKI_DLL( int getNumber(); )


/*
class Y;
class X
{
public:
	X(int x, Y* y) : m_y(y) {}
	X(double);
private:
	Y* m_y;
};
*/

#endif //STATKI_HPP
