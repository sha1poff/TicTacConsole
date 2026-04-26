#pragma once
#include "CellType.h"


class TicTacBoard
{
private:
    unsigned int boardsize; // размер поля
    CellType** cells;       // динамический двумерный массив ячеек
    bool bVictory = false;  // флаг состояния победы

    // вспомогательные методы проверки
    bool IsRowMade(unsigned int row);
    bool IsColumnMade(unsigned int col);
    bool IsDiagMade();
    bool IsBoardFull();

public:
    TicTacBoard(unsigned int size);
    TicTacBoard(TicTacBoard* board);
    virtual ~TicTacBoard();

    void Show(); // отрисовка поля с индексами строк и столбцов
    void SetCell(unsigned int xpos, unsigned int ypos, CellType ct);

    bool CheckLegal(unsigned int xpos, unsigned int ypos);
    bool CheckEndCondition(); // проверка, закончена ли игра
    bool IsVictory();         // возвращает true, если есть победитель

    unsigned int GetBoardsize() const;
};