#include "fasada.h"


Fasada::Fasada()
{
}


Fasada::~Fasada()
{
}

GameData Fasada::ConnectPlayer()
{
	//TODO add id generation
	string id;

	Game & game = Game::getInstance();
	deque<Position*> shipsPos = game.addPlayer(id);

	vector<MapPosition> myShips;

	for(int i = 0; i < shipsPos.size(); i++)
	{
		MapPosition pos;
		pos.x = shipsPos[i]->get_i;
		pos.x = shipsPos[j]->get_j;
		myShips.push_back(pos);
	}

	Info * gameInfo = game.getInfo(id);

	GameData dataToReturn;
	dataToReturn.GameMode = gameInfo->gameMode;
	dataToReturn.ID = id;
	dataToReturn.MyShips = myShips;
	

	return dataToReturn;
}