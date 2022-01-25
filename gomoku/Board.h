#pragma once

enum player { X_PLAYER = 1, O_PLAYER = -1 };
enum play  { NO_WIN = 0, X_WIN = 1, O_WIN = 2, DRAW = 3 };
enum cell { O = -1, NUL = 0, X = 1 };

const int FIELD_SIZE = 10;
const int WIN_SIZE = 5;

class Board
{
public:	
private:
	
	cell board[FIELD_SIZE][FIELD_SIZE];

	bool searchWin3(player player) const;
	bool searchWin(player player) const;
	bool searchDraw() const;
public:
	Board();
	~Board();

	bool makeMove(int x, int y, player player);
	play isWin() const;
	cell getCell(int x, int y) const;
};

