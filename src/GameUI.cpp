#include "GameUI.h"

void GameUI::initialize()
{
	int m, n, k;
		
	while (true) {
		//Take input from the user for row and check if it is a number
		m = inputNumber("Please enter the number of row: ");
		if (m == -1) {
			continue;
		}
		//Check if the input row is out of bound
		if (m < MIN_ROW || m > MAX_ROW) {
			cout << "Number of row has to be between " << MIN_ROW << " to " << MAX_ROW << endl;
			continue;
		}
		break;
	}

	while (true) {
		//Take input from the user for col and check if it is a number
		n = inputNumber("Please enter the number of col: ");
		if (n == -1) {
			continue;
		}
		//Check if the input col is out of bound
		if (n < MIN_COL || n > MAX_COL) {
			cout << "Number of col has to be between " << MIN_COL << " to " << MAX_COL << endl;
			continue;
		}
		break;
	}

	while (true) {
		//Take input from the user for k and check if it is a number
		k = inputNumber("Please enter the number of k (k in a row to win): ");
		if (k == -1) {
			continue;
		}
		//Check if the input k is out of bound
		if (k < 3 || (k > m && k > n)) {
			cout << "k cannot be smaller than 3 or larger than max(row, col)" << endl;
			continue;
		}
		break;
	}
	gameBoard = GameBoard(m, n, k);
}

int GameUI::inputNumber(const string& prompt)
{
	cout << prompt;
	string user_input;
	getline(cin, user_input);

	//Check if the inputs are numbers
	if (!isNumber(user_input)) {
		cout << "Please enter number only!!" << endl;
		return -1;
	}
	return stoi(user_input);
}

bool GameUI::isNumber(const string& s)
{
	for (const char& c : s) {
		if (isdigit(c) == 0) {
			return false;
		}
	}
	return true;
}

GameUI::GameUI()
{
	initialize();
}

void GameUI::run()
{
	//turn indicates whose turn currently is. 1 -> player1's turn, -1 -> player2's turn
	int turn = 1;
	GSTATUS game_status = GSTATUS::CONTINUE;
	while (true) {
		cout << "##########################################################" << endl;
		if (turn == 1) {
			cout << "Player 1's turn" << endl;
		}
		else {
			cout << "Player 2's turn" << endl;
		}
		gameBoard.drawBoard();

		//Ask the users if they want to undo a move if can undo
		if (gameBoard.canUndo()) {
			string isUndo;
			while (true) {
				cout << "Do you want to undo a move? (Y/N): ";
				getline(cin, isUndo);
				if (isUndo != "Y" && isUndo != "N") {
					cout << "Invalid Input! Please enter either Y for undo or N for not undo the last move." << endl;
					continue;
				}
				else {
					break;
				}
			}
			if (isUndo == "Y") { //User wants to undo
				gameBoard.undoMove();
				turn *= -1;
				continue;
			}
		}

		//Prompt the users to enter a row and a col to place their move
		int row, col;

		row = inputNumber("Please enter the number of row place your move: ");
		if (row == -1) {
			continue;
		}
		col = inputNumber("Please enter the number of col place your move: ");
		if (col == -1) {
			continue;
		}

		try {
			if (turn == 1) {
				game_status = gameBoard.makeMove(row - 1, col - 1, Square::PLAYER1);
			}
			else {
				game_status = gameBoard.makeMove(row - 1, col - 1, Square::PLAYER2);
			}
		}
		catch (invalid_argument& e) {
			cout << e.what() << endl;
			continue;
		}

		//Check if the game ends
		if (game_status == GSTATUS::CONTINUE) {
			turn *= -1;
			continue;
		}
		else if (game_status == GSTATUS::PLAYER1_WIN) {
			gameBoard.drawBoard();
			cout << "Player 1 wins!!!" << endl;
			break;
		}
		else if (game_status == GSTATUS::PLAYER2_WIN) {
			gameBoard.drawBoard();
			cout << "Player 2 wins!!!" << endl;
			break;
		}
		else {
			gameBoard.drawBoard();
			cout << "Draw, nobody wins." << endl;
			break;
		}
	}
}
