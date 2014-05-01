#pragma once
#include "square.h"
#define BOARD_WIDTH 32
#define BOARD_HEIGHT 32
class CBoard
{
public:
	CBoard(void);
	~CBoard(void);
	CSquare& GetSquare(int row, int col);
	void Reset();
	UINT SquareRowCount;
	UINT SquareColumnCount;
	bool GameOver;
	bool GameWon;
	void PeekSquare(int row, int col);
	void FlagSquare(int row, int col);
private:
	CSquare _Squares[BOARD_WIDTH][BOARD_HEIGHT];
	UINT _FlagCount;
	UINT _RevealedCount;
public:
	void UpdateAdjacentMineCount(int row, int col);
	void SetSize(int rowCount, int colCount);
private:
	void Reveal(int row, int col);
public:
	void UpdateWinStatus(void);
};

