
//#include "statki.hpp"//
#include "client.h"
//#include <iostream>//
//#include <string>//
//#include <queue>
//#include <deque>

/*
Game scenario:
1. Player A connects to the server and gives its ID invoking method Game.addPlayer(id), which returns random ships'positions
2. Player A waits for the second player to appear by repeatedly asking for the game state (based on which it can determine if second player has joined)
3. Player B joins the game by invoking Game.addPlayer(id)
4. Player B check if they can shoot or if they've been shot
5. PlayerA shoot (They have been set as the first player to attack because they've joined first).Player B check for changes to game state and reacts

*/
int main(){
	//1.
	std::cout << "Battleships!\n";
	Client clientA;
	clientA.connect();

	//2.
	clientA.inquireAndReact();
	clientA.inquireAndReact();
	clientA.inquireAndReact();

	//3.
	Client clientB;
	clientB.connect();

	//4.
	clientB.inquireAndReact();

	//5.
	clientA.inquireAndReact();
	clientB.inquireAndReact();

	//6.
	clientA.inquireAndReact();
	clientB.inquireAndReact();
	clientA.inquireAndReact();
	clientB.inquireAndReact();
	clientA.inquireAndReact();
	clientB.inquireAndReact();
	
	int wait;
	std::cin >> wait;
	return 0;
}