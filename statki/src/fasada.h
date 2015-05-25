#pragma once
#include "gameData.h"
#include "statki.hpp"
#include <ctime>

string GameModeToString(Mode mode);

string GetGameState(string playerID);

GameData ConnectPlayer();

ShotResponse Shoot(string playerID, string pos_i, string pos_j);