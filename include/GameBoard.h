#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>

#include "Constants.h"

using namespace std;

/**
 * Representation of the game board of a mnk-game
 *
 * Game board is represented by a 2D vector of Square, an enum where 1 -> player1 occupied,
 * 2 -> player2 occupied, and 0 -> unoccupied. The instance of the class will contain 
 * information of a board and methods that are used to manage the board and check game status. 
 * GameUI will contain an object of this class to print the board and manage the
 * board based on user input.
 *
 */
class GameBoard
{
	//number of row, col, and k
	int m_row, n_col, k_in_a_row, squares_count;
	//2D vector that represents the board
	vector<vector<Square>> board;
	//a stack contains the previous moves by their indices
	vector<pair<int, int>> undo_stack;

	/**
	* A helper function for drawing board based on what element is needed
	* 
	* @param element indicator of what to draw. 'h' -> header, 'r' -> a row, 'l' -> line that separates the rows
	* @param r parameter only needed when element is 'r'. It specifies the row to draw
	*/
	void drawElement(char element, int r = -1);
	
	/**
	* a helper function that checks if a move is valid. If new_square is Square::PLAYER1 or Square::PLAYER2, 
	* the move is valid if the specified square is Square::UNOCCUPIED, vise versa. 
	* The move is invalid if r and c are out of bound.
	*
	* @param r,c row and col the move will occure
	* @param new_square the square that will be changed to at the position
	* @return a bool indicates whether the move is valid
	*/
	bool isValidMove(int r, int c, Square new_square);

	/**
	* a helper function that return the current game status based on the information of last move
	* 
	* @param last_move_r, last_move_c row and col where last move placed
	* @param last_square variable to indicate which player was for the last move
	* @return GSTATUS::CONTINUE if the game has not come to an end, GSTATUS::PLAYER1_WIN if player 1 wins, 
	*	GSTATUS::PLAYER2_WIN if player 2 wins, GSTATUS::DRAW if it is a draw.
	*/
	GSTATUS checkGameStatus(int last_move_r, int last_move_c, Square last_square);

	/**
	* a helper function that check if there are k Squares in a row in certain direction based only on the last move
	* which means it only checks if the last move results in k in a row.
	* 
	* the direction represents by a character, where 'v'->vertical check, 'h'->horizontal check,
	* 'l'->left diagonal check, 'r'->right diagonal check
	*
	* @param last_move_r, last_move_c row and col where last move placed
	* @param last_square variable to indicate which player was for the last move
	* @param check_dir the direction the function is going to check for k in a row
	* @return a boolean indicates whether the last move results in k in a row in the specified direction
	*/
	bool isKInARow(int last_move_r, int last_move_c, Square last_square, char check_dir);

public:

	/**
	* Default Constructor which will initialize the board for a tic-tac-toe game,
	* where m_row = 3, n_col = 3, and k_in_a_row = 3.
	*/
	GameBoard();
	/** Construct a game board with m row, n col, and k in a row for win */
	GameBoard(int m, int n, int k);

	/*  Print out the current board  */
	void drawBoard();

	/**
	* Make a move by setting board[r][c] to new_square.
	* 
	* @param r,c row and col where the move going to occur
	* @param new_square the Square board[r][c] going to be set to
	* 
	* @return a GSTATUS which indicates whether the game ends after the move
	* @throws std::invalid_argument Thrown when r,c are out of bound, or board[r][c] is occupied but tring
	*	to occupy again
	*/
	GSTATUS makeMove(int r, int c, Square new_square);

	/**
	* Undo a move using the undo_stack. Set the previous move to UNOCCUPIED
	*
	* @return an bool indicates whether undo succeeds. 
	*/
	bool undoMove();

	/**
	* Check if the board can undo a move
	*
	* @return an bool indicates whether user can undo a move.
	*/
	bool canUndo();
};

#endif //GAMEBOARD_H

