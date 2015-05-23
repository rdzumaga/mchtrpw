using namespace std;

#include <string>
#include <vector>

struct MapPosition{
public:
	int x, y;
};

struct ShotPosition{
	int x, y;
	bool TargetHit;
};

class GameData{
public:
	string ID;
	string GameMode;
	vector<MapPosition> MyShips;
	vector<MapPosition> EnemyShots;
	vector<ShotPosition> MyShots;	
};


