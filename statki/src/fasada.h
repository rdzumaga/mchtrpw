#pragma once
#include "gameData.h"
#include "statki.hpp"
#include <ctime>

string GameModeToString(Mode mode);

string GetGameState(string playerID);

GameData ConnectPlayer();

