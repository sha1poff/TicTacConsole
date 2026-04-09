#include "pch.h"
#include "TicTacManager.h"


TicTacManager::TicTacManager() : board(nullptr), player1(nullptr), player2(nullptr), currentPlayer(nullptr) {}

bool TicTacManager::Init()
{
    unsigned int boardsize;
    string playerName;

    cout << "Введите число клеток поля (3-6): ";
    cin >> boardsize;

    if (boardsize < 3 || boardsize > 6)
    {
        cout << "Неверное число клеток поля" << endl;
        return false;
    }

    this->board = new TicTacBoard(boardsize);
    this->player1 = new TicTacPlayer();
    this->player2 = new TicTacPlayer();

    cin.ignore(); // очистка буфера после cin >> boardsize

    cout << "Введите имя игрока, играющего X: ";
    getline(cin, playerName);
    player1->SetupPlayer(playerName, CellType_X);

    cout << "Введите имя игрока, играющего O: ";
    getline(cin, playerName);
    player2->SetupPlayer(playerName, CellType_O);

    player1->SetBoard(board);
    player2->SetBoard(board);

    currentPlayer = player1;

    return true;
}

TicTacManager::~TicTacManager()
{
    delete this->player2;
    delete this->player1;
    delete this->board;
}

void TicTacManager::ShowBoard()
{
    this->board->Show();
}

void TicTacManager::MakeMove()
{
    ShowBoard();

    while (!currentPlayer->MakeMove())
    {
        cout << "Недопустимый ход, попробуйте еще раз" << endl;
        ShowBoard();
    }

    if (this->board->CheckEndCondition())
    {
        if (this->board->IsVictory())
            cout << "Игрок " << currentPlayer->GetName() << " победил!" << endl;
        else
            cout << "Ничья!" << endl;

        this->bGameFinished = true;
        ShowBoard();
        return;
    }

    // смена игрока
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool TicTacManager::IsGameFinished()
{
    return bGameFinished;
}