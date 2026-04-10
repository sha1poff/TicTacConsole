#include "pch.h"
#include "TicTacManager.h"
#include "TicTacHumanPlayer.h"
#include "TicTacComputerPlayer.h"


TicTacManager::TicTacManager() : board(nullptr), player1(nullptr), player2(nullptr), currentPlayer(nullptr) {}

TicTacManager::~TicTacManager()
{
    delete this->player2;
    delete this->player1;
    delete this->board;
}


bool TicTacManager::Init()
{
    unsigned int boardsize;
    string playerName;
    int playertype;

    cout << "Введите число клеток поля (3-6): ";
    cin >> boardsize;

    if (boardsize < 3 || boardsize > 6)
    {
        cout << "Неверное число клеток поля" << endl;
        return false;
    }

    this->board = new TicTacBoard(boardsize);
 
    cout << "Введите тип игрока #1 (1 - Человек, любое другое число - Компьютер):";
    cin >> playertype;
    if (playertype == 1)
        this->player1 = new TicTacHumanPlayer();
    else
        this->player1 = new TicTacComputerPlayer();

    cout << "Введите тип игрока #2 (1 - Человек, любое другое число - Компьютер):";
    cin >> playertype;
    if (playertype == 1)
        this->player2 = new TicTacHumanPlayer();
    else
        this->player2 = new TicTacComputerPlayer();


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