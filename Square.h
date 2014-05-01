#pragma once
class CSquare
{
public:
	CSquare(void);
	~CSquare(void);
	bool IsMine;
	int AdjacentMineCount;
	bool IsFlagged;
	bool IsHidden;
	bool WasGameOver;
	void Reset(void);
};

