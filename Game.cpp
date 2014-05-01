#include "StdAfx.h"
#include "Game.h"


CGame::CGame(void)

	: _LeftMargin(0)
	, _TopMargin(1)
	, IsHintMode(false)
	, _SquareWidth(24)
{
}


CGame::~CGame(void)
{
}

int CGame::GetWindowWidth()
{
	int width;
	width=17+_LeftMargin+(_Board.SquareRowCount*_SquareWidth);
	return width;
}
int CGame::GetWindowHeight()
{
	int height;
	height=59+_TopMargin+(_Board.SquareColumnCount*_SquareWidth);
	return height;
}
void CGame::PaintBoard(HDC hdc, HWND hWnd)
{
	COLORREF color=0x79FF75;
	if(_Board.GameOver)
	{
		color=_Board.GameWon ? 0xFFFC54:0xFF8D42;
	}
	SetBkColor(hdc,color);
	RECT rect;
	for(UINT col=0; col<_Board.SquareColumnCount; col++)
	{
		for(UINT row=0; row<_Board.SquareRowCount; row++)
		{
			CSquare& square=_Board.GetSquare(row,col);
			//override drawing flags/hidden.
			bool isFlagged=square.IsFlagged&&!IsHintMode;
			bool isHidden=square.IsHidden&&!IsHintMode&&!_Board.GameOver;

			rect.left=(col*_SquareWidth)+_LeftMargin;
			rect.top=(row*_SquareWidth)+_TopMargin;
			rect.right=(col*_SquareWidth)+_LeftMargin+_SquareWidth;
			rect.bottom=(row*_SquareWidth)+_TopMargin+_SquareWidth;
			PaintSquareBorder(hdc, rect, square);
			if(isFlagged)
			{
				PaintFlaggedSquare(hdc, rect, square);
			}
			else
			{
				if(isHidden)
				{
					PaintHiddenSquare(hdc, rect, square);
				}
				else
				{
					if(square.IsMine)
					{
						PaintMineSquare(hdc, rect, square);
					}
					else
					{
						PaintNumberSquare(hdc, rect, square);
					}
				}
			}

		}
	}
}


void CGame::OnLeftClick(int xpos, int ypos)
{
	if(!_Board.GameOver)
	{
		int col = (xpos - _LeftMargin) / _SquareWidth;
		int row = (ypos -_TopMargin) / _SquareWidth;
		_Board.PeekSquare(row, col);
	}
}

void CGame::OnRightClick(int xpos, int ypos)
{
	if(!_Board.GameOver)
	{
		int col = (xpos - _LeftMargin) / _SquareWidth;
		int row = (ypos -_TopMargin) / _SquareWidth;
		_Board.FlagSquare(row,col);
	}
}

void CGame::PaintNumberSquare(HDC hdc, RECT& rect, CSquare& square)
{
	HBRUSH brush=CreateHatchBrush(HS_DIAGCROSS, RGB(127.5,0,255));
	HGDIOBJ brushOld ;
	brushOld=SelectObject(hdc,brush);
	Rectangle(hdc,rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc,brushOld);
	DeleteObject(brush);
	LPCTSTR pszCount=NULL;
	switch (square.AdjacentMineCount)
	{
	case 1:
		pszCount=_T("1");
		break;
	case 2:
		pszCount=_T("2");
		break;
	case 3:
		pszCount=_T("3");
		break;
	case 4:
		pszCount=_T("4");
		break;
	case 5:
		pszCount=_T("5");
		break;
	case 6:
		pszCount=_T("6");
		break;
	case 7:
		pszCount=_T("7");
		break;
	case 8:
		pszCount=_T("8");
		break;
	default:
		break;
	}
	if(pszCount!=NULL)
		TextOut(hdc, rect.left+8,rect.top+4,pszCount,1);

}
void CGame::PaintHiddenSquare(HDC hdc, RECT& rect, CSquare& square)
{
	HBRUSH brush=CreateHatchBrush(HS_DIAGCROSS, RGB(255,255,127));
	HGDIOBJ brushOld;
	brushOld=SelectObject(hdc,brush);
	Rectangle(hdc,rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc,brushOld);
	DeleteObject(brush);
}
void CGame::PaintFlaggedSquare(HDC hdc, RECT& rect, CSquare& square)
{
	HBRUSH brush=CreateHatchBrush(HS_DIAGCROSS, RGB(255,0,0));
	HGDIOBJ brushOld ;
	brushOld=SelectObject(hdc,brush);
	Rectangle(hdc,rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc,brushOld);
	DeleteObject(brush);
}
void CGame::PaintMineSquare(HDC hdc, RECT& rect, CSquare& square)
{
	HBRUSH brush=CreateHatchBrush(square.WasGameOver ? HS_BDIAGONAL : HS_DIAGCROSS, RGB(127,51,0));
	HGDIOBJ brushOld ;
	brushOld=SelectObject(hdc,brush);
	Rectangle(hdc,rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc,brushOld);
	DeleteObject(brush);
}
void CGame::PaintSquareBorder(HDC hdc, RECT& rect, CSquare& square)
{
	HPEN pen= CreatePen(PS_SOLID, 3,RGB(0,0,0));
	HGDIOBJ penOld;
	penOld=SelectObject(hdc, pen);
	Rectangle(hdc,rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc,penOld);
	DeleteObject(pen);
}


void CGame::Reset()
{
	IsHintMode=false;
	_Board.Reset();
}


void CGame::SetBoardSize(int rowCount, int colCount)
{
	_Board.SetSize(rowCount,colCount);
	Reset();
}
