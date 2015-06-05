#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <iostream>
#include "game.h" 

using namespace std;

class Client
{
public:
	Client();
	~Client();
	static int iToInt(string target);
	static int jToInt(string target);
	static string numToLetter(int num);
	void connect();
	void inquireAndReact();
	int shoot(string target);

	//attributes
	string board[N][N];
	string opponentBoard[N][N];
	string id;
private:
	void loadShipsPos(deque<Position*> shipsPos);
	void printBoards();
	void attack();
	void reactToAttack(Info* gameInfo);

};

#endif