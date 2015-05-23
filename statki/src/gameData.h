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

class GameData{
public:
	string ID;
	string GameMode;
	string MyShips;
	string EnemyShots;
	string MyShots;	
};


