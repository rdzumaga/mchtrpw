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
	default:
		return "IDLE";

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

	

	for (int i = 0; i < shipsPos.size(); i++)
	{
		
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
		response.TargetHit = game.shoot((pos_i), (pos_j));
		response.GameMode = GameModeToString(game.getInfo(playerID).gameMode);		
		return response;
	}




}

FASADA_DLL(UpdateResponse Update(string playerID))
{
	static int updateCount = 0;

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

	if (response.GameMode == "FINISHED")
	{
		if (updateCount == 1)
		{
			updateCount = 0;
			game.reset();
		}
		else
		{
			updateCount++;
		}
	}
	

	return response;
}