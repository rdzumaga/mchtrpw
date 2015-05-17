
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


	/*std::string idA, idB;
	cin >> idA;
	std::deque<Position*> shipsA = game->addPlayer(idA);
	cout << "Welcome playerA!\nAwaiting playerB to come and enter theirs ID...\n";

	//2.
	cout << "Player A waits for player B...\n";
	//printGameState(game);
	cout << "\nPlayer B, enter your ID:\n";

	//3.
	std::cin >> idB;
	cout << "Welcome playerB. Your ID is " << idB << "\n*******************************************************************\n";
	std::deque<Position*> shipsB = game->addPlayer(idB);

	//print boards
	setShipsPos(shipsA, shipsB);
	printBoards(idA, idB);
	
	//4.
	cout << "----------------------------------------------------\nThe game begins!\n\n";
	cout << "Player B checks if they have been attacked and if they can shoot...\n";
	printGameState(game);
	gstate = *(game->getGameState());
	if (gstate.attacks.size() > 0)
		cout << "Player B is under attack!\n";
	else if (gstate.attackedPlayerId == idB)
		cout << "Player B is waiting for the attack from playerA\n";

	//5.
	//printPlayersId(idA, idB);
	//printGameState(game);
	cout << "It is now the turn of player with the ID=" << gstate.attackingPlayerId << endl << endl;
	cout << "Player, enter the field nr you want to shoot, eg.: A1\n";
	string target;
	cin >> target;
	int result = shootWrapper(target, idA, game);

	cout << "Player B checks if they have been attacked and if they can shoot...\n";
	printGameState(game);
	gstate = *(game->getGameState());
	if (gstate.attacks.size() > 0){
		cout << "Player B is under attack!\n";
		//note the attack on board
		Attack * attack = gstate.attacks[0];
		int i, j;
		i = attack->pos->get_i();
		j = attack->pos->get_j();
		mapB[i][j] = "! ";
	}
	else if (gstate.attackedPlayerId == idB)
		cout << "Player B is waiting for the attack from playerA\n";

	if (result == -1)
		cout << "Error while shooting field " << target << endl;
	else if (result == 0){
		cout << "You missed! No ship found at " << target << endl;
		mapA_opponent[iToInt(target)][jToInt(target)] = "X ";
	}
	else if (result == 1){
		cout << "Well done! You hit a ship!\n";
		mapA_opponent[iToInt(target)][jToInt(target)] = "! ";
	}

	printBoards(idA, idB);
	cout << "Player, enter the field nr you want to shoot, eg.: A1\n";
	cin >> target;
	result = shootWrapper(target, idA, game);

	cout << "Player B checks if they have been attacked and if they can shoot...\n";
	printGameState(game);
	gstate = *(game->getGameState());
	if (gstate.attacks.size() > 0){
		cout << "Player B is under attack!\n";
		//note the attack on board
		Attack * attack = gstate.attacks[0];
		int i, j;
		i = attack->pos->get_i();
		j = attack->pos->get_j();
		mapB[i][j] = "! ";
	}
	else if (gstate.attackedPlayerId == idB)
		cout << "Player B is waiting for the attack from playerA\n";

	if (result == -1)
		cout << "Error while shooting field " << target << endl;
	else if (result == 0){
		cout << "You missed! No ship found at " << target << endl;
		mapA_opponent[iToInt(target)][jToInt(target)] = "X ";
	}
	else if (result == 1){
		cout << "Well done! You hit a ship!\n";
		mapA_opponent[iToInt(target)][jToInt(target)] = "! ";
	}

	printBoards(idA, idB);
		

		
	//	printGameState(game);

	//	printGameState(game);


		//game->begin();


	*/
	int wait;
	std::cin >> wait;
	return 0;
}