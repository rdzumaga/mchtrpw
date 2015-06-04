using namespace std;

#include <string>
#include <vector>

//struct MapPosition{
//public:
//	int x, y;
//
//	bool operator==(const MapPosition& mp1)
//	{
//		return true;
//	}
//};
//
//struct ShotPosition{
//	int x, y;
//	bool TargetHit;
//};
//
//typedef vector<MapPosition> MapPos;
//typedef vector<ShotPosition> ShotPos;

/**
 * \class	GameData
 *
 * \brief	Used to pass mulitple value to client.
 * 			GameMode - current game state.
 * 			MyShips - specially formated string containing player's ships positions. 
 */
class GameData{
public:
	string ID;
	string GameMode;
	string MyShips;
	string EnemyShots;
	string MyShots;
};

/**
 * \class	ShotResponse
 *
 * \brief	GameMode - current game state.
 * 			TargetHit - 0 if shot missed, 1 if shot was on target.
 * 
 */
class ShotResponse{
public:
	string GameMode;
	int TargetHit;
};

/**
 * \class	UpdateResponse
 *
 * \brief	ID - identifier for in-game active player.
 * 			EnemyShots - specially formatted string containing enemy shots positions.
 * 			GameMode - current game state.
 *  
 */
class UpdateResponse{
public:
	string ID;
	string EnemyShots;
	string GameMode;
};