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
Assumptions:
	- Each field can have a pointer to only one ship
	- Each player has a different ID (string?)
	- The game board's size is 10x10. The Fields are numbered from 0 till 9
	- A ships' position on the game board is defined by its starting position (uppermost segment or the first segment on the left side) 
	  and its orientation. So if lenght=3, orientation=horizontal and pos=(1,1), then the ship is placed on the following fields: (1,1), (1,2), (1,3)
	- A player cannot shoot the same field more than once (should be implemented in the client)
	- A player can only shoot when it's their turn (should be implemented by client)
	- The player can shoot only fields with indexes between 0 and 9 (checked by client)
*/

#include <deque>
#include <string>
#include <queue>

//typedef boost::shared_ptr<Game> game_ptr;

const int N = 10;
const int shipsNr = 10;
const int ERROR = -1;

class Player;

class Field;
class Ship;
class Position;
class Attack;
class GameState;
class Game;

//			0		1		2			3
enum Mode { IDLE, WAITING, ONGOING, FINISHED };

class Attack{
public:
	Attack();
	Attack(Position* pos, bool successful);
	Position * pos;
	bool successful;
};

class Info{
public:
	Info(Player* player, Mode gameMode);
	
	bool playerIsUnderAttack;
	Mode gameMode;
	Attack* lastAttack;
};

class Game{
public:
	static Game& getInstance(){
		static Game instance;
		return instance;
	}

	std::deque<Position*> addPlayer(std::string id);
	Info* getInfo(std::string playerId);
	
	/*
	returns:
	-1: error
	 0: shot missed
	 1: shot successful
	//TODO 2: ship sunk?
	*/
	int shoot(int i, int j);
	
private:
	Player* attacker;
	Player* attacked;
	Mode gameState;

	void switchActivePlayer();
	Player* getPlayer(std::string playerId);
	void finish();
	Game();
	Game(Game const &) = delete;
	void operator=(Game const &) = delete;
};

class Position{
public:
	Position(){}
	Position(int i, int j) : i(i), j(j) {}
	int get_i();
	int get_j();
private:
	int i;
	int j;
};

class Field{
public:
	Field();
	void attach(Ship* ship);
	void notify();
	bool isEmpty();
private:
	Ship* ship;
};

class Board{
public:
	Board(){}
	void shootField(int i, int j);
	Field fields[N][N];
	bool canPlaceShip(int i, int j, int length, int dx, int dy);
	void placeShip(Ship* ship);
};

class Ship{
public:
	enum Orientation { HORIZONTAL, VERTICAL };
	Ship(Player* owner, int length, Orientation or, int i, int j);
	void update();
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
	Player();
	Player(std::string id, bool isFirstPlayer);
	bool underAttack(int i, int j);
	bool hasLost();
	std::deque<Position*> getShipsPos();
	Attack* getLastAttack();
	
	void update();
	void toggleActive();
	bool isActive();
	std::string getId();
	
private:
	Board board;
	int remainingShipUnits;
	std::deque<Ship*> ships;
	bool sustainedDamage;
	std::string IP;
	bool activeFlag;
	std::queue<Attack *> receivedAttacks;

	void placeShipsRandomly();
	Ship* placeShipRandomly(int length, Ship::Orientation or);
};


const int statkiLen[] = { 5, 4, 4, 3, 3, 3, 2, 2, 2, 2 };

const Ship::Orientation statkiOrientation[] = {
	Ship::Orientation::HORIZONTAL,
	Ship::Orientation::VERTICAL
};






//------------------------------------------------

//! Example C++ calculation. This function return a number.
STATKI_DLL( int getNumber(); )



class Y;
class X
{
public:
	X(int x, Y* y) : m_y(y) {}
	//X(double);
private:
	Y* m_y;
};

class Y{
public:
	Y(int in){ j = in; }
	int j;
};

#endif //STATKI_HPP
