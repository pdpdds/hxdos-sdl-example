#include "Board.h"

//const int Board::FIELD_SIZE = 3;
//const int Board::WIN_SIZE = 3;

#define TEST

#define TEST2



Board::Board()
{
	
	int i, j;			// counters for for-cycles
	for (i = 0; i < FIELD_SIZE; i++)
	{
		for(j = 0; j < FIELD_SIZE; j++)
			board[i][j] = NUL;
	}
}


Board::~Board()
{
}

bool Board::makeMove(int x, int y, player player)
{
	if ((x >= 0) && (x < FIELD_SIZE) && (y >= 0) && (y < FIELD_SIZE) && (board[x][y] == NUL))
	{
		if (player == X_PLAYER)
			board[x][y] = X;
		else								// if (player == O_PLAYER)
			board[x][y] = O;

		return true;
	}
	else
		return false;

}


play Board::isWin()	const					
{
		// only for WIN_SIZE==5
		int i, j;			// counters for for-cycle


		// rows and columns (analyzes by fives of cells)
		for (i = 0; i < FIELD_SIZE; i++)
		{
			for (j = 0; j < FIELD_SIZE; j++)
			{

				//if ( ( (i + 4) < FIELD_SIZE ) && ( (j + 4) < FIELD_SIZE ) ) // mistake!!! condition ( i + 4 ) < FIELD_SIZE is excess
				if ( (j + 4) < FIELD_SIZE )
				{
					// rows
					if (board[i][j + 0] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3] + board[i][j + 4] == 5)
						return X_WIN;

					else if (board[i][j + 0] + board[i][j + 1] + board[i][j + 2] + board[i][j + 3] + board[i][j + 4] == -5)
						return O_WIN;

					// columns
					else if (board[j + 0][i] + board[j + 1][i] + board[j + 2][i] + board[j + 3][i] + board[j + 4][i] == 5)
						return X_WIN;

					else if (board[j + 0][i] + board[j + 1][i] + board[j + 2][i] + board[j + 3][i] + board[j + 4][i] == -5)
						return O_WIN;


				}
			}
		}

		// diagonals (analyzes by fives of cells)

		// diagonals from left up to right down
		for (i = 0; i < FIELD_SIZE - WIN_SIZE + 1; i++)		// untill i < 6
		{
			for (j = 0; j < FIELD_SIZE - WIN_SIZE + 1; j++)	// untill j < 6
			{
				if (board[i + 0][j + 0] + board[i + 1][j + 1] + board[i + 2][j + 2] + board[i + 3][j + 3] + board[i + 4][j + 4] == 5)
					return X_WIN;
				else if (board[i + 0][j + 0] + board[i + 1][j + 1] + board[i + 2][j + 2] + board[i + 3][j + 3] + board[i + 4][j + 4] == -5)
					return O_WIN;
			}

		}

		// diagonals from left down to right up
		for (i = FIELD_SIZE; i > FIELD_SIZE - 1 - WIN_SIZE - 1; i--)  // untill i > 3
		{
			for (j = 0; j < FIELD_SIZE - WIN_SIZE + 1; j++)	// untill j < 6
			{
				if (board[i - 0][j + 0] + board[i - 1][j + 1] + board[i - 2][j + 2] + board[i - 3][j + 3] + board[i - 4][j + 4] == 5)
					return X_WIN;
				else if (board[i - 0][j + 0] + board[i - 1][j + 1] + board[i - 2][j + 2] + board[i - 3][j + 3] + board[i - 4][j + 4] == -5)
					return O_WIN;
			}

		}

	if (searchDraw() == true)
		return DRAW;
	else
		return NO_WIN;

	/*		
	// central diagonals. Not necessary, because they are already looked through in the previous cycle
	for (j = 0; j < FIELD_SIZE; j++)
	{
	if (((j - 4) < 0) && ((j + 4) < FIELD_SIZE))
	{
	if (board[j + 0][j + 0] + board[j + 1][j + 1] + board[j + 2][j + 2] + board[j + 3][j + 3] + board[j + 4][j + 4] == 5)
	return X_WIN;

	else if (board[j + 0][j + 0] + board[j + 1][j + 1] + board[j + 2][j + 2] + board[j + 3][j + 3] + board[j + 4][j + 4] == -5)
	return O_WIN;

	else if (board[FIELD_SIZE - 1 - j - 0][j + 0] + board[FIELD_SIZE - 1 - j - 1][j + 1] + board[FIELD_SIZE - 1 - j - 2][j + 2] + board[FIELD_SIZE - 1 - j - 3][j + 3] + board[FIELD_SIZE - 1 - j - 4][j + 4] == 5)
	return X_WIN;

	else if (board[FIELD_SIZE - 1 - j - 0][j + 0] + board[FIELD_SIZE - 1 - j - 1][j + 1] + board[FIELD_SIZE - 1 - j - 2][j + 2] + board[FIELD_SIZE - 1 - j - 3][j + 3] + board[FIELD_SIZE - 1 - j - 4][j + 4] == -5)
	return O_WIN;

	}
	}
	*/

	/*
	// another realization of isWin(). Not good and quick
	if (searchWin(X_PLAYER) == true)
		return X_WIN;
	else if (searchWin(O_PLAYER) == true)
		return O_WIN;
	else if (searchDraw() == true)
		return DRAW;
	else
		return NO_WIN;
	*/


}

cell Board::getCell(int x, int y) const
{
	return board[x][y];
}

bool Board::searchWin3(player player) const
{
	cell val;
	if (player == X_PLAYER)				
		val = X;
	else									// if (player == O_PLAYER)
		val = O;


	int i, j;								// counters for for-cycle
	for (i = 0; i < FIELD_SIZE; i++)
		if ((board[i][0] == val) && (board[i][1] == val) && (board[i][2] == val))
			return true;

	for (j = 0; j < FIELD_SIZE; j++)
		if ((board[0][j] == val) && (board[1][j] == val) && (board[2][j] == val))
			return true;
	
	if ((board[0][0] == val) && (board[1][1] == val) && (board[2][2] == val))
		return true;

	if ((board[0][2] == val) && (board[1][1] == val) && (board[2][0] == val))
		return true;

	return false;
}

bool Board::searchDraw() const
{
	int i, j;								// counters for for-cycles
	for (i = 0; i < FIELD_SIZE; i++)
	{
		for (j = 0; j < FIELD_SIZE; j++)
		{
			if (board[i][j] == NUL)
				return false;
		}		
	}

	return true;
}

bool Board::searchWin(player player) const
{
	cell val;
	if (player == X_PLAYER)
		val = X;
	else									// if (player == O_PLAYER)
		val = O;

	int count;								// variable for accounting the same signs going in row (переменн? для подсчета одинаковых знаков, идущих подря?
	int i, j;								// counter for for-cycle

	// looks through rows
	count = 0;
	for (i = 0; i < FIELD_SIZE; i++)
	{
		for (j = 0; j < FIELD_SIZE; j++)
		{
			if ((board[i][j] == val))
			{
				count++;
				if (count == WIN_SIZE)
					return true;
			}
			else
				count = 0;
		}
	}

	// looks through columns
	count = 0;
	for (i = 0; i < FIELD_SIZE; i++)
	{
		for (j = 0; j < FIELD_SIZE; j++)
		{
			if ((board[j][i] == val))
			{
				count++;
				if (count == WIN_SIZE)
					return true;
			}
			else
				count = 0;
		}
	}

	return false;
}
