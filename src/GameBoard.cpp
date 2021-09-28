#include "GameBoard.h"

bool GameBoard::isValidMove(int r, int c, Square new_square)
{
	//Check if r and c are out of bound
	if (r < 0 || r >= m_row || c < 0 || c >= n_col) {
		return false;
	}
	//Check when new_square is UNOCCUPIED
	if (new_square == Square::UNOCCUPIED) {
		if (board[r][c] == Square::UNOCCUPIED) {
			return false;
		}
		return true;
	}
	//Check when new_square is PLAYER1 or PLAYER2
	else {
		if (board[r][c] != Square::UNOCCUPIED) {
			return false;
		}
		return true;
	}
}

GSTATUS GameBoard::checkGameStatus(int last_move_r, int last_move_c, Square last_square)
{
	//if last move set a square to unoccupied (only can happen when undo occurs),
	//return GSTATUS::COTINUE because the game cannot end with an undo.
	if (last_square == Square::UNOCCUPIED) {
		return GSTATUS::CONTINUE;
	}
	
	//a string contains 4 characters, each indicates a direction to check for the isKInARow() function
	//v -> vertical, h -> horizontal, l -> left to right diagonal, r -> right to left diagonal
	string checks = "vhlr";
	for (char c : checks) {
		if (isKInARow(last_move_r, last_move_c, last_square, c)) {
			if (last_square == Square::PLAYER1) {
				return GSTATUS::PLAYER1_WIN;
			}
			else {
				return GSTATUS::PLAYER2_WIN;
			}
		}
	}

	//Check if the games come to a draw
	if (squares_count == m_row * n_col) {
		return GSTATUS::DRAW;
	}

	return GSTATUS::CONTINUE;
}

bool GameBoard::isKInARow(int last_move_r, int last_move_c, Square last_square, char check_dir)
{
	//Check if check_dir is invalid
	if (check_dir != 'v' && check_dir != 'h' && check_dir != 'l' && check_dir != 'r') {
		throw invalid_argument("check_dir has to specify to one of the following char: 'v', 'h', 'l', 'r'");
	}
	//Get a copy of last_move_r and last_move_c
	int lr = last_move_r, lc = last_move_c;
	//Count how many Squares are currently in a row
	int count = 0;
	//v_dir, h_dir indicates the direction the function going to check
	int v_dir, h_dir;
	switch (check_dir) {
	case 'v':
		v_dir = 1;
		h_dir = 0;
		break;
	case 'h':
		v_dir = 0;
		h_dir = 1;
		break;
	case 'l':
		v_dir = 1;
		h_dir = 1;
		break;
	case 'r':
		v_dir = 1;
		h_dir = -1;
		break;
	}
	//Count the same Sqaures in the first direction
	while (lr >= 0 && lr < m_row && lc >= 0 && lc < n_col && count < k_in_a_row && board[lr][lc] == last_square) {
		count++;
		lr += v_dir;
		lc += h_dir;
	}
	if (count == k_in_a_row) {
		return true;
	}
	else {
		lr = last_move_r - v_dir;
		lc = last_move_c - h_dir;
	}
	//Count the same Sqaures in the second direction
	while (lr >= 0 && lr < m_row && lc >= 0 && lc < n_col && count < k_in_a_row && board[lr][lc] == last_square) {
		count++;
		lr -= v_dir;
		lc -= h_dir;
	}

	return count == k_in_a_row;
}

GameBoard::GameBoard()
	:m_row{ 3 }, n_col{ 3 }, k_in_a_row{ 3 }, squares_count{ 0 }
{
	board = vector<vector<Square>>(m_row, vector<Square>(n_col, Square::UNOCCUPIED));
}

GameBoard::GameBoard(int m, int n, int k)
	: m_row{ m }, n_col{ n }, k_in_a_row{ k }, squares_count{ 0 }
{
	board = vector<vector<Square>>(m_row, vector<Square>(n_col, Square::UNOCCUPIED));
}

void GameBoard::drawBoard()
{
	drawElement('h');
	for (int i = 0; i < m_row; i++) {
		drawElement('l');
		drawElement('r', i+1);
	}
	drawElement('l');
	drawElement('h');
}

GSTATUS GameBoard::makeMove(int r, int c, Square new_square)
{
	if (isValidMove(r, c, new_square)) {
		board[r][c] = new_square;

		//Push to the undo stack and increase the count only when player occupies a square
		if (new_square != Square::UNOCCUPIED) {
			undo_stack.push_back(make_pair(r, c));
			squares_count++;
		}
		return checkGameStatus(r, c, new_square);
	}
	else {
		throw invalid_argument("The move is invalid. A move has to place at row and col that are in bound, and the square has to be changed either from UNOCCUPIED to PLAYER or PLAYER to UNOCCUPIED");
	}
}

bool GameBoard::undoMove()
{
	if (undo_stack.empty()) {
		return false;
	}
	pair<int, int> last_move = undo_stack.back();
	undo_stack.pop_back();
	squares_count--;
	makeMove(last_move.first, last_move.second, Square::UNOCCUPIED);
	return true;
}

bool GameBoard::canUndo()
{
	return !undo_stack.empty();
}

void GameBoard::drawElement(char element, int r)
{
	// throw expection when r is not valid and element to draw is 'r'
	if (element == 'r' && (r < 1 || r > m_row)) {
		throw invalid_argument("r need to be ranged from 1 to m_row if row element is needed to be drawed");
	}
	// draw element based on input
	switch (element) {
	case 'h':
		cout << "   ";
		for (int i = 1; i <= n_col; i++) {
			//Checking the digit of i to allign
			if (i < 10) {
				cout << " " << i << "  ";
			}
			else if (i <= MAX_COL && i >= 10) {
				cout << " " << i << " ";
			}
		}
		cout << endl;
		break;
	case 'l':
		cout << "  ";
		for (int i = 0; i < n_col; i++) {
			cout << " " << "---";
		}
		cout << endl;
		break;
	case 'r':
		//Checking the digit of r to allign
		if (r < 10) {
			cout << " " << r;
		}
		else if (r <= MAX_ROW && r >= 10) {
			cout  << r;
		}
		for (int i = 0; i < n_col; i++) {
			Square squre = board[r - 1][i];
			if (squre == Square::UNOCCUPIED) {
				cout << "|" << "   ";
			}
			else if (squre == Square::PLAYER1) {
				cout << "|" << " O ";
			}
			else {
				cout << "|" << " X ";
			}
		}
		cout << "|" << " " << r << endl;
		break;
	}
}