#include "TicTacRandomPlayer.h"


TicTacRandomPlayer::TicTacRandomPlayer()
{
}

TicTacRandomPlayer::~TicTacRandomPlayer()
{
}

bool TicTacRandomPlayer::MakeMove()
{
	unsigned int row, col;

	row = (unsigned int)(rand() % 6);
	col = (unsigned int)(rand() % 6);

	if (this->board->CheckLegal(col, row))
	{
		this->board->SetCell(col, row, this->cellType);
		return true;
	}

	return false;
}