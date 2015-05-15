
#include "statki.hpp"//
//#include "client.h"
#include <iostream>//
#include <string>//
#include <queue>
#include <deque>

using namespace std;

string mapA[10][10] = {
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " }
};

string mapA_opponent[10][10] = {
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " }
};

string mapB[10][10] = {
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " }
};


string mapB_opponent[10][10] = {
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " },
		{ "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- ", "- " }
};

void printAttacks(deque<Attack*> a){
	cout << "Attacks:\n";
	if (a.size()){
		for (int i = 0; i < a.size(); i++){
			cout << "(" << a.at(i)->pos->get_i() << ", " << a.at(i)->pos->get_j() << "): " << a.at(i)->successful << endl;
		}
	}
}
void printGameState(Game* game){
	GameState& gstate = *(game->getGameState());
	cout << "--------------------------------------------------------\n";
	cout << "mode=" << gstate.mode << endl;
	cout << "attackingId=" << gstate.attackingPlayerId << endl;
	cout << "attackedID=" << gstate.attackedPlayerId << endl;
	printAttacks(gstate.attacks);
	cout << "--------------------------------------------------------\n";
	if (gstate.mode == Mode::ONGOING)
		cout << "\nBoth players present. Let's start!\n";
	else if (gstate.mode = Mode::WAITING)
		cout << "\nWaiting for the other player...\n";


}


void printShipsPos(std::deque<Position*> poss){
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPrinting ships positions now:\n";
	for (int i = 0; i < poss.size(); i++){
		cout << "(" << poss[i]->get_i() << ",";//
		cout << poss[i]->get_j()<< "), ";
	}
}

void addPlayer(Game* game, string id){
	cout << "---------------\ngame->addPlayer(" << id << ")\n";
	std::deque<Position*> ships = game->addPlayer(id);
	printShipsPos(ships);
}
void printPlayersId(string idA,string idB){
	cout << "PlayerA: " << idA << ", PlayerB: " << idB << endl;
}
void printBoards(string idA, string idB){
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "Boards' states for playerA with id=" << idA << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\tMy board:\t\t\t Opponent's board:\n\n";
	cout << "  A B C D E F G H I J\t\t\t  A B C D E F G H I J\n";
	for (int i = 0; i < N; i++){
		cout << i << " ";
		for (int j = 0; j < N; j++){
			cout << mapA[i][j];
		}
		cout << "\t\t\t" << i << " ";
		for (int j = 0; j < N; j++){
			cout << mapA_opponent[i][j];
		}
		cout << endl;
	}

	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "Boards' states for playerB with id=" << idB << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\tMy board:\t\t\t Opponent's board:\n\n";
	cout << "  A B C D E F G H I J\t\t\t  A B C D E F G H I J\n";
	for (int i = 0; i < N; i++){
		cout << i << " ";
		for (int j = 0; j < N; j++){
			cout << mapB[i][j];
		}
		cout << "\t\t\t" << i << " ";
		for (int j = 0; j < N; j++){
			cout << mapB_opponent[i][j];
		}
		cout << endl;
	}
}

void setShipsPos(std::deque<Position*> shipsA, std::deque<Position*> shipsB){
	for (int k = 0; k < shipsA.size(); k++){
		Position* shipPos = shipsA[k];
		mapA[shipPos->get_i()][shipPos->get_j()] = "s ";
	}

	for (int k = 0; k < shipsB.size(); k++){
		Position* shipPos = shipsB[k];
		mapB[shipPos->get_i()][shipPos->get_j()] = "s ";
	}

}

int iToInt(string target){
	string i_c(1, target[1]);
	return atoi(i_c.c_str());
}

int jToInt(string target){
	string j_c(1, target[0]);
	if (j_c == "A")
		return 0;
	else if (j_c == "B")
		return 1;
	else if (j_c == "C")
		return 2;
	else if (j_c == "D")
		return 3;
	else if (j_c == "E")
		return 4;
	else if (j_c == "F")
		return 5;
	else if (j_c == "G")
		return 6;
	else if (j_c == "H")
		return 7;
	else if (j_c == "I")
		return 8;
	else if (j_c == "J")
		return 9;
	else
		cout << "Error, field " << target << " does not exist. Exit the game and start again\n";
	return 0;
}

int shootWrapper(string target, string id, Game* game){
	int i, j;
	i = iToInt(target);
	j = jToInt(target);
	return game->shoot(i, j, id);
}

/*
Game scenario:
1. Player A connects to the server and gives its ID invoking method Game.addPlayer(id), which returns random ships'positions
2. Player A waits for the second player to appear by repeatedly asking for the game state (based on which it can determine if second player has joined)
3. Player B joins the game by invoking Game.addPlayer(id)
4. Player B check if they can shoot or if they've been shot
5. PlayerA shoot (They have been set as the first player to attack because they've joined first).Player B check for changes to game state and reacts

*/
int main(){

	//Client * clientA = new Client;
	Game *game = new Game();
	GameState& gstate=*game->getGameState();
	//1.
	cout << "Battleships!\nIf you would like to play, enter your playerID (any string):";
	string idA, idB;
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

		/*
		int i, j;
		i = 0;
		j = 5;
		bool response = game->shoot(i, j, idA);
		cout << "Just shot (" << i << "," << j << "). The result is: " << response;

		j = 4;
		response = game->shoot(i, j, idB);
		cout << "Just shot (" << i << "," << j << "). The result is: " << response;
		*/
	
	int wait;
	cin >> wait;
	return 0;
}