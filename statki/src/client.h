#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>
#include "statki.hpp" 

using namespace std;

class Client
{
public:
	Client();
	~Client();
	static int iToInt(string target);
	static int jToInt(string target);
	void connect();
	void inquireAndReact();
	void shoot();

	//attributes
	string board[N][N];
	string opponentBoard[N][N];
	string id;

};

#endif