#include "fasada.h"
#include <iostream>


FASADA_DLL(string GameModeToString(Mode mode))
{
	switch (mode) {
	case IDLE:
		return "IDLE";
		break;
	case WAITING:
		return "WAITING";
		break;
	case ONGOING:
		return "ONGOING";
		break;
	case FINISHED:
		return"FINISHED";
		break;
	}
}

FASADA_DLL(string GetGameState(string playerID))
{
	Game & game = Game::getInstance();
	Info gameInfo = game.getInfo(playerID);

	return GameModeToString(gameInfo.gameMode);
}

FASADA_DLL(GameData ConnectPlayer())
{
	string id;
	string myShips = "";
	srand(time(NULL));
	id = to_string(rand() % 100);

	Game & game = Game::getInstance();
	deque<Position*> shipsPos = game.addPlayer(id);

	//vector<MapPosition> myShips;

	for (int i = 0; i < shipsPos.size(); i++)
	{
		/*MapPosition pos;
		pos.x = shipsPos[i]->get_i();
		pos.y = shipsPos[i]->get_j();
		myShips.push_back(pos);*/
		int x, y;
		x = shipsPos[i]->get_i();
		y = shipsPos[i]->get_j();
		myShips += std::to_string(x);
		myShips += "-";
		myShips += std::to_string(y);
		myShips += ";";

	}

	Info gameInfo = game.getInfo(id);

	GameData dataToReturn;


	dataToReturn.GameMode = GameModeToString(gameInfo.gameMode);
	dataToReturn.ID = id;
	dataToReturn.MyShips = myShips;
	dataToReturn.EnemyShots = "";
	dataToReturn.MyShots = "";

	return dataToReturn;
}

FASADA_DLL(ShotResponse Shoot(string playerID, int pos_i, int pos_j))
{
	Game & game = Game::getInstance();
	Info info = game.getInfo(playerID);
	ShotResponse response;

	if (info.playerIsUnderAttack == true)
	{
		response.GameMode = GameModeToString(info.gameMode);
		response.TargetHit = false;
		return response;
	}
	else
	{
		response.GameMode = GameModeToString(game.getInfo(playerID).gameMode);
		response.TargetHit = game.shoot((pos_i), (pos_j));
		return response;
	}




}

FASADA_DLL(UpdateResponse Update(string playerID))
{
	Game & game = Game::getInstance();
	Info info = game.getInfo(playerID);
	UpdateResponse response;
	string enemyShots = "";
	std::queue<Attack*> enemyAttacks = info.receivedAttacks;

	for (int i = 0; i < info.receivedAttacks.size(); i++)
	{
		Attack* current = enemyAttacks.front();
		enemyAttacks.pop();
		int x, y;
		x = current->pos->get_i();
		y = current->pos->get_j();
		enemyShots += std::to_string(x);
		enemyShots += "-";
		enemyShots += std::to_string(y);
		enemyShots += ";";
	}

	if (info.playerIsUnderAttack == false)
	{
		response.ID = playerID;
	}
	else
	{
		response.ID = "";
	}

	
	response.GameMode = GameModeToString(info.gameMode);
	response.EnemyShots = enemyShots;
	

	return response;
}