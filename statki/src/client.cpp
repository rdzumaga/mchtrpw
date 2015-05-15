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

