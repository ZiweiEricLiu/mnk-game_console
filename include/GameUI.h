#ifndef GAMEUI_H
#define GAMEUI_H

#include <Gameboard.h>
#include <string>

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

	/** 
	* Initialize the UI. This method will be called in the default constructor.
	* It constructs the game board by taking inputs from users. If the inputs are not valid,
	* this method will show the reason and keep prompting until the users re-enter a valid input.
	*/
	void initialize();

	/**
	* helper function that prompts user to input a number. If the input is not a number, it will 
	* notice the user by printing to cout and return -1
	* 
	* @param prompt the prompt for the user input
	* @return return the integer form of the input number. -1 if it is not a number.
	*/
	int inputNumber(const string& prompt);
	
	/**
	* helper function that checks if a string is a number.
	* 
	* @param s string that is going to be checked
	* @return true if the string is a number, false otherwise.
	*/
	bool isNumber(const string& s);

public:

	GameUI();

	/** Run the UI until the game ends*/
	void run();

};


#endif //GAMEUI_H
