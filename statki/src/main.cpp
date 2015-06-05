

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


void testAddPlayer(){
	//test if first player connects and gets the ships'positions
	const int expectedShipsPositionsNum = 5 + 4 + 4 + 3 + 3 + 3 + 2 + 2 + 2 + 2;
	std::string id = "1";
	bool isFirstPlayer = true;
	std::deque<Position*> shipsPos;

	Game& game = Game::getInstance();
	game.reset();
	shipsPos = game.addPlayer(id);
	if (shipsPos.size() == 0){
		std::cout << "Error! Player 1 wasn't added to the game even though he should have been\n";
		//BOOST_ERROR("Error! Player 1 wasn't added to the game even though he should have been\n");
	}
	//BOOST_CHECK_EQUAL(shipsPos.size(), expectedShipsPositionsNum);


	//test if second player connect and gets the ships'positions
	id = "2";
	shipsPos = game.addPlayer(id);
	if (shipsPos.size() == 0){
		std::cout << "Error! Player 2 wasn't added to the game even though he should have been\n";
		//BOOST_ERROR("Error! Player 2 wasn't added to the game even though he should have been\n");
	}
	//BOOST_CHECK_EQUAL(shipsPos.size(), expectedShipsPositionsNum);

	//test if second player connect and gets the ships'positions
	id = "3";
	shipsPos = game.addPlayer(id);
	if (shipsPos.size() == 0){
		std::cout << "Correct! Player 3 wasn't added to the game. Great!\n";
		//BOOST_ERROR("Error! Player 2 wasn't added to the game even though he should have been\n");
	}
	//BOOST_CHECK_EQUAL(shipsPos.size(), expectedShipsPositionsNum);
}

void testGetInfo(){
	Game& game = Game::getInstance();
	game.reset();
	Info info = game.getInfo("sfdfs");
	std::string id1 = "1";
	std::string id2 = "2";
	game.addPlayer(id1);


}



int main(){


	//1.
	std::cout << "Battleships!\n";



	//2.
//	clientA.inquireAndReact();
	//clientA.inquireAndReact();
	//clientA.inquireAndReact();

	//3.
	


	for (int i = 0; i < 10; i++){
		std::cout << i << ": \n";
		Client clientA;
		clientA.connect();
		Client clientB;
		clientB.connect();
		Game::getInstance().reset();
	}

	/*
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
	clientB.inquireAndReact();*/


	int wait;
	std::cin >> wait;
	//_CrtDumpMemoryLeaks();
	return 0;
}