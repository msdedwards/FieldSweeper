#include "StdAfx.h"
#include "Square.h"


CSquare::CSquare(void)
{
	Reset();
}


CSquare::~CSquare(void)
{
}


void CSquare::Reset(void)
{
	IsMine=false;
	IsHidden=true;
	IsFlagged=false;
	AdjacentMineCount=0;
	WasGameOver=false;
}
