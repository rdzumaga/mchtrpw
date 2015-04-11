
#include "statki.hpp"
#include <iostream>
#include <string>
#include <queue>
#include <deque>

using namespace std;

void printAttacks(deque<Attack*> a){
	cout << "Attacks:\n";
	if (a.size()){
		for (int i = 0; i < a.size(); i++){
			cout << "(" << a.at(i)->pos->i << ", " << a.at(i)->pos->j << "): " << a.at(i)->successful << endl;
		}
	}
}
void printGameState(Game* game){
	GameState gstate = game->state;
	cout << "mode=" << gstate.mode << endl;
	cout << "attackingId=" << gstate.attackingPlayerId << endl;
	cout << "attackedID=" << gstate.attackedPlayerId << endl;
	printAttacks(gstate.attacks);

}
void addPlayer(Game* game, string id){
	cout << "---------------\ngame->addPlayer(id)\n";
	game->addPlayer(id);

}

void printShipsPos(std::deque<Position*> poss){
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPrinting ships positions now:\n";
	for (int i = 0; i < poss.size(); i++){
		cout << "(" << poss[i]->i << ",";//
		cout << poss[i]->j << "), ";
	}
}

int main(){
	cout << "Gra w statki\n";
	Game *game = new Game();
	printGameState(game);

	string idA, idB;
	idA = "A";
	idB = "B";

	addPlayer(game, idA);
	printGameState(game);

	addPlayer(game, idB);
	printGameState(game);

	std::deque<Position*> shipsA = game->getShipsPos(idA);
	printShipsPos(shipsA);


	std::deque<Position*> shipsB = game->getShipsPos(idB);
	printShipsPos(shipsB);

	game->begin();

	int i, j;
	i = 0;
	j = 5;
	bool response = game->shoot(i, j, idA);
	cout << "Just shot (" << i << "," << j << "). The result is: " << response;

	j = 4;
	response = game->shoot(i, j, idB);
	cout << "Just shot (" << i << "," << j << "). The result is: " << response;

	int wait;
	cin >> wait;
	return 0;
}