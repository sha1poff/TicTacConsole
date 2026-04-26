#pragma once

#include "TicTacPlayer.h"


class TicTacComputerPlayer :
    public TicTacPlayer
{
private:
    int Minimax(TicTacBoard* nodeBoard, int depth, bool isMaximizing, int alpha, int beta);

public:
    TicTacComputerPlayer();
    virtual ~TicTacComputerPlayer();
    virtual bool MakeMove();
};

