/**
 * \file statki.hpp
 * \brief the C++ statki library  */

#ifndef STATKI_HPP
#define STATKI_HPP

/*
Assumptions:
	- Each field can have a pointer to only one ship
	- Each player has a different ID (string)
	- The game board's size is 10x10. The Fields are numbered from 0 till 9
	- A ships' position on the game board is defined by its starting position (uppermost segment or the first segment on the left side) 
	  and its orientation. So if lenght=3, orientation=horizontal and pos=(1,1), then the ship is placed on the following fields: (1,1), (1,2), (1,3)
	- A player cannot shoot the same field more than once (implemented in the client)
	- A player can only shoot when it's their turn ( implemented by client)
	- The player can shoot only fields with indexes between 0 and 9 (checked by client)
*/

#include <deque>
#include <string>
#include <queue>
#include <memory>

const int N = 10;
const int shipsNr = 10;
const int ERROR = -1;

class Player;
class Ship;

typedef std::shared_ptr<Ship> ShipPtr;

//			0		1		2			3
enum Mode { IDLE, WAITING, ONGOING, FINISHED };


/**
* \class    Position
*
* \brief    Simple class representing a position on game board
*/
class Position{
public:
	///default constructor
	Position(){}
	///constructor
	Position(int i, int j) : i(i), j(j) {}


	/** \brief Get method.
	* \return row index for this position on the board
	*/
	int get_i();

	/** \brief Get method.
	* \return column index for this position on the board
	*/
	int get_j();
private:
	int i;
	int j;
};





/**
* \class    Attack
*
* \brief    Simple class representing where an attack took place and if it was successful
*/
class Attack{
public:
	///default constructor
	Attack();

	///constructor
	Attack(Position* pos, bool successful);
	Position * pos;
	bool successful;
};


/**
* \class    Info
*
* \brief   Simple class for updating a player about current game state
*/
class Info{
public:
	///constructor
	Info(Player* player, Mode gameMode);
	std::queue<Attack *> receivedAttacks;
	bool playerIsUnderAttack;
	Mode gameMode;
};




/**
* \class    Field
*
* \brief    simple class for notifying the ship placed there that it was attacked
*/
class Field{
public:

	///default constructor
	Field();

	/** \brief attach ship method.
	* \param ship Handle to the ship that will be placed on this field
	*
	* This method places a ship on this field. This makes it possible for the ship to be notified of an attack later on
	*/
	void attach(ShipPtr ship);

	///method notifying a ship that it was attacked
	void notify();

	///checks if a ship is placed on this field
	bool isEmpty();
private:
	ShipPtr ship;
};


/**
* \class    Board
*
* \brief    Simple class containing the list of fields on the board
*/
class Board{
public:
	///default constructor
	Board(){}

	/** \brief shoot field method.
	* \param i row index of the targeted field.
	* \param j column index of the targeted field.
	*
	* This method notifies a field that it was shot.
	*/
	void shootField(int i, int j);

	/** \brief check if a ship can be placed on that filed
	* \param i number of row (value from 0 to 9).
	* \param j number of column (value from 0 to 9).
	* \param lenght length of the ships to be placed
	* \param dx indicates vertical orientation if bigger than 0
	* \param dy indicates horizontak orientation if bigger than 0
	* \return 1 if there was a ship placed on the targeted field, 0 otherwise.
	*
	* Checks if all fields needed for a ship of given length and orientation are free and if there are no ships on neighbouring fields
	*/
	bool canPlaceShip(int i, int j, int length, int dx, int dy);

	///place the ship on board positions assigned to it
	void placeShip(ShipPtr ship);

	Field fields[N][N];
};


/**
* \class    Ship
*
* \brief    Class representing a ship
*/
class Ship{
public:
	enum Orientation { HORIZONTAL, VERTICAL };

	/** \brief constructor
	* \param owner Player who owns this ship
	* \param lenght length of the ships
	* \param or Orientation of ship on the board
	* \param i number of row (value from 0 to 9).
	* \param j number of column (value from 0 to 9).
	*/
	Ship(Player* owner, int length, Orientation or, int i, int j);

	///method for upadting the ship (that it was attacked) and notifying its owner about the attack
	void update();

	/** \brief get ship segments' positions
	* \return a deque of positions
	*/
	std::deque<Position*> getPositions();

private:
	Player* owner;
	int length;
	int remainingSegements;
	Orientation orientation;
	Position pos;

	///method notifying the owner about the attack on their ship
	void notify();
};



/**
* \class    Player
*
* \brief    Class representing a player
*/
class Player{
public:
	///dummy constructor for avoiding null pointer exceptions
	Player();

	/** \brief constructor
	* \param id player ID
	* \param isFirstPlayer a flag indicating if player was the first to join the game
	*/
	Player(std::string & id, bool isFirstPlayer);

	/** \brief Get the positions of player's ships
	* \return list of ships' positions
	*/
	std::deque<Position*> getShipsPos();
	
	/** \brief react to attack from the opponent
	* \param i number of row of the targeted field (value from 0 to 9).
	* \param j number of column of the targeted field(value from 0 to 9).
	* \return 1 if there was a ship placed on the targeted field, 0 otherwise.
	*/
	bool underAttack(int i, int j);

	///check if the player has lost (all ships sunk)
	bool hasLost();

	///update the player about damage sustained from opponent's attack
	void update();

	///set player as active (attacking) player
	void toggleActive();

	///check if player is active
	bool isActive();

	///get method for player's ID
	std::string getId();

	///get method for queue containing the received attacks
	std::queue<Attack *> getReceivedAttacks();
	
	
private:
	Board board;
	int remainingShipUnits;
	std::deque<ShipPtr> ships;
	bool sustainedDamage;
	std::string ID;
	bool activeFlag;
	std::queue<Attack *> receivedAttacks;
	
	///method placing ships on player's board in a random way
	void placeShipsRandomly();

	/** \brief private method placing one ship of given lenght and orientation on the board
	* \param lenght length of the ships
	* \param or Orientation of ship on the board
	* \return newly created and placed ship
	*/
	ShipPtr placeShipRandomly(int length, Ship::Orientation or);
};


const int statkiLen[] = { 5, 4, 4, 3, 3, 3, 2, 2, 2, 2 };

const Ship::Orientation statkiOrientation[] = {
	Ship::Orientation::HORIZONTAL,
	Ship::Orientation::VERTICAL
};


#endif //STATKI_HPP
