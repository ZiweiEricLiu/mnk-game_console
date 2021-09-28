#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MIN_ROW = 3, MIN_COL = 3;
const int MAX_ROW = 50, MAX_COL = 50;

enum class Square {
	UNOCCUPIED,
	PLAYER1,
	PLAYER2
};

enum class GSTATUS {
	CONTINUE,
	PLAYER1_WIN,
	PLAYER2_WIN,
	DRAW
};

#endif
