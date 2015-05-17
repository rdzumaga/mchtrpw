#include "client.h"


Client::Client() {

	//initialize the board with nothing ("- ")
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			board[i][j] = opponentBoard[i][j] = "- ";
		}
	}
}

Client::~Client()
{
}

int Client::iToInt(string target){
	string i_c(1, target[1]);
	return atoi(i_c.c_str());
}

int Client::jToInt(string target){
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

string Client::numToLetter(int num){
	if (num == 0)
		return "A";
	else if (num == 1)
		return "B";
	else if (num == 2)
		return "C";
	else if (num == 3)
		return "D";
	else if (num == 4)
		return "E";
	else if (num == 5)
		return "F";
	else if (num == 6)
		return "G";
	else if (num == 7)
		return "H";
	else if (num == 8)
		return "I";
	else if (num == 9)
		return "J";

}
void Client::connect(){
	cout << "Player is connecting to server. Please enter player id (any string)\n";
	cin >> id;
	Game & game = Game::getInstance();
	deque<Position*> shipsPos = game.addPlayer(id);
	loadShipsPos(shipsPos);
}

void Client::loadShipsPos(deque<Position*> shipsPos){
	for (int k = 0; k < shipsPos.size(); k++){
		Position* pos = shipsPos[k];
		board[pos->get_i()][pos->get_j()] = "s ";
	}
	printBoards(); 
}

void Client::printBoards(){
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "Boards' states for player with id=" << id << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\tMy board:\t\t\t Opponent's board:\n\n";
	cout << "  A B C D E F G H I J\t\t\t  A B C D E F G H I J\n";
	for (int i = 0; i < N; i++){
		cout << i << " ";
		for (int j = 0; j < N; j++){
			cout << board[i][j];
		}
		cout << "\t\t\t" << i << " ";
		for (int j = 0; j < N; j++){
			cout << opponentBoard[i][j];
		}
		cout << endl;
	}
}

void Client::inquireAndReact(){
	cout << "\n__________________ info for player " << id << " _________________________\n";
	Game & game = Game::getInstance();
	GameState * state = game.getGameState();
	
	if (state->mode == WAITING)
		cout << "\nPlayer " << id << " is waiting for the second player to join the game\n.......................................................\n";
	else if (state->mode == ONGOING){
		if (state->attackingPlayerId == id)
			attack(state);
		else if (state->attackedPlayerId == id)
			reactToAttack(state);
		else
			cout << "Error:Player id doesn't match attacker or attacked it!\n";
	}
	else if (state->mode == IDLE)
		cout << "Game state is idle...\n";
	else
		cout << "Game state is finished\n";
}

void Client::attack(GameState* state){
	cout << "Player " << id << ", it is your turn to shoot.\nEnter the field nr you want to shoot, eg.: A1\n";
	string target;
	int result;
	cin >> target;
	result=shoot(target);

	if (result == -1)
		cout << "Error while shooting field " << target << endl;
	else {
		if (result == 0){
			cout << "You missed! No ship found at " << target << endl;
			opponentBoard[iToInt(target)][jToInt(target)] = "X ";
			printBoards();
		}
		else {
			while (result == 1){
				cout << "Well done! You hit a ship!\n";
				opponentBoard[iToInt(target)][jToInt(target)] = "! ";
				printBoards();
				attack(Game::getInstance().getGameState());
				result = 0;
			}
		}
	}	
}

int Client::shoot(string target){
	int i, j;
	i = iToInt(target);
	j = jToInt(target);
	return Game::getInstance().shoot(i, j, id);
}
void Client::reactToAttack(GameState* state){	
	cout << "react To Attack()\n";
	if (!state->attacks.empty()){		
		Attack * attack = state->attacks.front();
		state->attacks.pop(); 
		Position* pos = attack->pos;
		cout << "The opponent shot at " << Client::numToLetter(pos->get_i()) << pos->get_j() << endl;
		int i, j;
		i = attack->pos->get_i();
		j = attack->pos->get_j();
		if (attack->successful){
			cout << "Oh no, you've been hit!\n";
			board[i][j] = "! ";
		}
		else{
			cout << "Your opponent missed!\n";
			board[i][j] = "X ";
		}
	}
	else if (state->attackedPlayerId == id)
		cout << "\nWaiting for the opponent to make a move...\n";

	printBoards();
}