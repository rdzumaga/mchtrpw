using namespace std;

#include <string>
#include <vector>


#ifdef FASADA_EXPORTS
//Workaround for Windows DLL library exports
#define FASADA_DLL(X) __declspec(dllexport)X
#else
//Workaround for Unix Shared Library exports
#define FASADA_DLL(X) X
#endif



/**
 * \class	GameData
 *
 * \brief	Used to pass mulitple value to client.
 * 			GameMode - current game state.
 * 			MyShips - specially formated string containing player's ships positions. 
 */
class FASADA_DLL(GameData){
public:
	string ID;
	string GameMode;
	string MyShips;	
};

/**
 * \class	ShotResponse
 *
 * \brief	GameMode - current game state.
 * 			TargetHit - 0 if shot missed, 1 if shot was on target.
 * 
 */
class FASADA_DLL(ShotResponse){
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
class FASADA_DLL(UpdateResponse){
public:
	string ID;
	string EnemyShots;
	string GameMode;
};