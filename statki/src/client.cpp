#include "client.h"
#include <cstdlib> 
#include <ctime>

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
	srand(time(NULL));
	//id = to_string(rand() % 100);
	cout << "Player is connecting to server. Player id is: " +id+ "\n";
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
	Info gameInfo = game.getInfo(id);
	//GameState * state = game.getGameState();
	
	if (gameInfo.gameMode == WAITING)
		cout << "\nPlayer " << id << " is waiting for the second player to join the game\n.......................................................\n";
	else if (gameInfo.gameMode == ONGOING){
		
		gameInfo = game.getInfo(id);
		if (!gameInfo.playerIsUnderAttack)
			attack();
		else
			cout << "Waiting for the opponent to make a move...\n";
	}

	else if (gameInfo.gameMode == IDLE)
		cout << "Game state is idle...\n";
	else
		cout << "You lost :(\nGame state is finished\n";
}

void Client::attack(){
	cout << "Player " << id << ", it is your turn to shoot.\nEnter the field nr you want to shoot, eg.: A1\n";
	string target;
	int result;
	cin >> target;
	result=shoot(target);
	
	//attack is a recursive function for client. Check for changes in game state for this iteration
	Info info = Game::getInstance().getInfo(id);
	if (info.gameMode == FINISHED){
		cout << "\n\nYOU WON!!!!!!!\n";
		return;
	}

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
				attack();
				result = 0;
			}
		}
	}	
}

int Client::shoot(string target){
	int i, j;
	i = iToInt(target);
	j = jToInt(target);
	return Game::getInstance().shoot(i, j);
}
void Client::reactToAttack(Info* gameInfo){
	cout << "react To Attack()\n";
	
	
	
	printBoards();
}