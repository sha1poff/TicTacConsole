#include "pch.h"
#include "TicTacComputerPlayer.h"


TicTacComputerPlayer::TicTacComputerPlayer()
{
}

TicTacComputerPlayer::~TicTacComputerPlayer()
{
}

bool TicTacComputerPlayer::MakeMove()
{
    unsigned int row, col;
    cout << "Игрок " << name << ", ваш ход..." << endl;
    cout << "Введите строку: ";
    cin >> row;
    cout << "Введите столбец: ";
    cin >> col;

    if (this->board->CheckLegal(col, row))
    {
        this->board->SetCell(col, row, this->cellType);
        return true;
    }

    return false;
}