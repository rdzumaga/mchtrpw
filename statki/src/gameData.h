using namespace std;

#include <string>
#include <vector>

struct Position{
public:
	int x, y;
};

struct ShotPosition{
	int x, y;
	bool TargetHit;
};

class gameData{
public:
	string ID;
	string GameMode;
	vector<Position> MyShips;
	vector<Position> EnemyShots;
	vector<ShotPosition> MyShots;	
};


