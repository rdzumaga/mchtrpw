#include "fasada.h"
#include <iostream>

GameData ConnectPlayer()
{
	string id;
	srand(time(NULL));
	id = to_string(rand() % 100);
	
	Game & game = Game::getInstance();
	deque<Position*> shipsPos = game.addPlayer(id);

	vector<MapPosition> myShips;

	for(int i = 0; i < shipsPos.size(); i++)
	{
		MapPosition pos;
		pos.x = shipsPos[i]->get_i();
		pos.y = shipsPos[i]->get_j();
		myShips.push_back(pos);
	}

	Info * gameInfo = game.getInfo(id);

	GameData dataToReturn;

	switch (gameInfo->gameMode) {
	case IDLE:
		dataToReturn.GameMode = "IDLE";
		break;			
	case WAITING:
		dataToReturn.GameMode = "WAITING";
		break;
	case ONGOING:
		dataToReturn.GameMode = "ONGOING";
		break;
	case FINISHED:
		dataToReturn.GameMode = "FINISHED";
		break;
	}

	dataToReturn.ID = id;
	dataToReturn.MyShips = myShips;
	
	

	return dataToReturn;
}