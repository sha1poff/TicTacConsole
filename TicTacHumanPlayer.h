#pragma once

#include "pch.h"
#include "TicTacPlayer.h"


class TicTacHumanPlayer :
    public TicTacPlayer
{
public:
    TicTacHumanPlayer();
    virtual ~TicTacHumanPlayer();

    virtual bool MakeMove(); // запрос координат у пользователя
};