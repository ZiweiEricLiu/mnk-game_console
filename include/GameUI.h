#ifndef GAMEUI_H
#define GAMEUI_H

#include <Gameboard.h>

/**
 * A Class that handles visualizing the game and handling user inputs
 *
 * GameUI contains an object of GameBoard. It will try to retrieve game information from the board
 * to print it to the players. It will also parse user inputs to change the board using methods of the 
 * GameBoard object.
 * 
 * The method run() will keep running the UI until the game ends.
 *
 */
class GameUI
{
	GameBoard gameBoard;

	/** Initialize the UI. This method will be called in the default constructor.*/
	void initialize();

public:

	GameUI();

	/** Run the UI until the game ends*/
	void run();

};


#endif //GAMEUI_H
