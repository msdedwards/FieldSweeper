#include "StdAfx.h"
#include "Board.h"
#include <ctime>


CBoard::CBoard(void) : 
    SquareRowCount(16),
    SquareColumnCount(16)
{
	Reset();
}



CBoard::~CBoard(void)
{
}


CSquare& CBoard::GetSquare(int row, int col)
{
	return _Squares[row][col];
}


void CBoard::Reset()
{
	GameOver=false;
	GameWon=false;
	for(UINT col=0; col<SquareColumnCount; col++)
	{
		for(UINT row=0; row<SquareRowCount; row++)
		{
			CSquare& square=GetSquare(row,col);
			square.Reset();
		}
	}
	srand((unsigned int)time(NULL));
	for (int randMines=(SquareRowCount*SquareColumnCount)/8; randMines>0; )
	{
		int randcol= rand() % SquareColumnCount;
		int randrow= rand() % SquareRowCount;

		CSquare& square=GetSquare(randrow,randcol);
		if(!square.IsMine)
		{
		square.IsMine=true;
		UpdateAdjacentMineCount(randrow-1,randcol-1);
		UpdateAdjacentMineCount(randrow-1,randcol);
		UpdateAdjacentMineCount(randrow-1,randcol+1);
		UpdateAdjacentMineCount(randrow,randcol-1);
		UpdateAdjacentMineCount(randrow,randcol+1);
		UpdateAdjacentMineCount(randrow+1,randcol-1);
		UpdateAdjacentMineCount(randrow+1,randcol);
		UpdateAdjacentMineCount(randrow+1,randcol+1);
		randMines--;
		}
	}
}
void CBoard::UpdateAdjacentMineCount(int row, int col)
{
	if(row>=0&&col>=0&&row<SquareRowCount&&col<SquareColumnCount)
	{
		CSquare& square=GetSquare(row,col);
		square.AdjacentMineCount++;
	}
}
void CBoard::PeekSquare(int row, int col)
{
	CSquare& square=GetSquare(row,col);
	if(square.IsMine)
	{
		if(!square.IsFlagged)
		{
			GameOver=true;
			square.WasGameOver=true;
		}
	}
	else
	{
		Reveal(row, col);
	}
}
void CBoard::FlagSquare(int row, int col)
{
	CSquare& square=GetSquare(row,col);
	square.IsFlagged=!square.IsFlagged;
	if(square.IsMine)
	{
		if(square.IsFlagged)
		{
			_FlagCount++;
		}
		else
		{
			_FlagCount--;
		}
		UpdateWinStatus();
	}
}




void CBoard::SetSize(int rowCount, int colCount)
{
	SquareRowCount=rowCount;
	SquareColumnCount=colCount;
}


void CBoard::Reveal(int row, int col)
{
	if(row>=0&&col>=0&&row<SquareRowCount&&col<SquareColumnCount)
	{
		CSquare& square=GetSquare(row,col);
		if(square.IsHidden&&!square.IsMine)
		{
			_RevealedCount++;
			UpdateWinStatus();
			square.IsHidden=false;
			if(square.AdjacentMineCount==0)
			{
				Reveal(row-1,col-1);
				Reveal(row-1,col);
				Reveal(row-1,col+1);
				Reveal(row,col-1);
				Reveal(row,col+1);
				Reveal(row+1,col-1);
				Reveal(row+1,col);
				Reveal(row+1,col+1);
			}
		}
	}
}


void CBoard::UpdateWinStatus(void)
{
	GameOver=GameWon=((SquareColumnCount*SquareRowCount)-_FlagCount-_RevealedCount)==0;
}
