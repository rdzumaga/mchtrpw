#pragma once
#include "gameData.h"
#include "statki.hpp"
#include <ctime>

string GameModeToString(Mode mode);

string GetGameState(string playerID);

GameData ConnectPlayer();

ShotResponse Shoot(string playerID, int pos_i, int pos_j);

UpdateResponse Update(string playerID);