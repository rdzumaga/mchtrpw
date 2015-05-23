#include "fasada.h"



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
		pos.x = shipsPos[i]->get_j();
		myShips.push_back(pos);
	}

	Info * gameInfo = game.getInfo(id);

	GameData dataToReturn;
	dataToReturn.GameMode = gameInfo->gameMode;
	dataToReturn.ID = id;
	dataToReturn.MyShips = myShips;
	

	return dataToReturn;
}