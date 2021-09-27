#include "GameBoard.h"

GameBoard::GameBoard()
	:m_row{ 3 }, n_col{ 3 }, k_in_a_row{ 3 }
{
	board = vector<vector<int>>(m_row, vector<int>(n_col, 0));
}

GameBoard::GameBoard(int m, int n, int k)
	: m_row{ m }, n_col{ n }, k_in_a_row{ k }
{
	board = vector<vector<int>>(m_row, vector<int>(n_col, 0));
}
