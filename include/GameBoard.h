#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

using namespace std;

/**
 * Representation of the game board of a mnk-game
 *
 * Game board is represented by a 2D vector of integers, where 1 -> player1 occupied,
 * 2 -> player2 occupied, and 0 -> unoccupied. The instance of the class will contain 
 * information of a board and methods that are used to manage the board and check game status. 
 * GameUI will contain an object of this class to print the board and manage the
 * board based on user input.
 *
 */
class GameBoard
{
	int m_row, n_col, k_in_a_row;
	vector<vector<int>> board;

public:

	/**
	* Default Constructor which will initialize the board for a tic-tac-toe game,
	* where m_row = 3, n_col = 3, and k_in_a_row = 3.
	*/
	GameBoard();
	GameBoard(int m, int n, int k);
};

#endif //GAMEBOARD_H

