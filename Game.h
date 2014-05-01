#pragma once
#include "board.h"

//#define windowWidth _LeftMargin+(_SquareWidth*_Board.SquareRowCount)
//#define windowHeight 500

class CGame
{
public:
	CGame(void);
	~CGame(void);
	void PaintBoard(HDC hdc, HWND hWnd);
	void OnLeftClick(int xpos, int ypos);
	void OnRightClick(int xpos, int ypos);
	bool IsHintMode;
private:
	CBoard _Board;
	int _LeftMargin;
	int _TopMargin;
	void PaintSquareBorder(HDC hdc, RECT& rect, CSquare& square);
	void PaintNumberSquare(HDC hdc, RECT& rect, CSquare& square);
	void PaintHiddenSquare(HDC hdc, RECT& rect, CSquare& square);
	void PaintMineSquare(HDC hdc, RECT& rect, CSquare& square);
	void PaintFlaggedSquare(HDC hdc, RECT& rect, CSquare& square);
	int _SquareWidth;
public:
	void Reset();
	void SetBoardSize(int rowCount, int colCount);
	int GetWindowWidth();
	int GetWindowHeight();
};

