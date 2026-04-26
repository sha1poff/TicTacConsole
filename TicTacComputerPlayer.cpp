#include "pch.h"
#include "TicTacComputerPlayer.h"
#include "TicTacBoardMonteCarloEvaluator.h"


TicTacComputerPlayer::TicTacComputerPlayer()
{
}

TicTacComputerPlayer::~TicTacComputerPlayer()
{
}

int TicTacComputerPlayer::Minimax(TicTacBoard* nodeBoard, int depth, bool isMaximizing, int alpha, int beta)
{
    // проверка завершения игры в симуляции
    if (nodeBoard->CheckEndCondition())
    {
        if (nodeBoard->IsVictory()) {
            // возвращаем оценку в зависимости от того чей сейчас ход
            return isMaximizing ? -10 : 10;
        }
        return 0; // ничья
    }

    // ограничение глубины для стабильной работы на больших полях
    if (depth == 0) return 0;

    unsigned int size = nodeBoard->GetBoardsize();

    if (isMaximizing)
    {
        int bestScore = -1000;
        for (unsigned int i = 0; i < size; i++) {
            for (unsigned int j = 0; j < size; j++) {
                if (nodeBoard->CheckLegal(j, i))
                {
                    // создаем копию состояния доски
                    TicTacBoard* childBoard = new TicTacBoard(nodeBoard);
                    childBoard->SetCell(j, i, this->cellType);

                    int score = Minimax(childBoard, depth - 1, false, alpha, beta);
                    delete childBoard; // освобождение памяти

                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, bestScore);
                    if (beta <= alpha) return bestScore; // альфа-бета отсечение
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        CellType opponentType = (this->cellType == CellType_X) ? CellType_O : CellType_X;

        for (unsigned int i = 0; i < size; i++) {
            for (unsigned int j = 0; j < size; j++) {
                if (nodeBoard->CheckLegal(j, i))
                {
                    TicTacBoard* childBoard = new TicTacBoard(nodeBoard);
                    childBoard->SetCell(j, i, opponentType);

                    int score = Minimax(childBoard, depth - 1, true, alpha, beta);
                    delete childBoard;

                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, bestScore);
                    if (beta <= alpha) return bestScore; // альфа-бета отсечение
                }
            }
        }
        return bestScore;
    }
}

bool TicTacComputerPlayer::MakeMove()
{
    int bestScore = -1000;
    int bestX = -1;
    int bestY = -1;

    unsigned int size = this->board->GetBoardsize();

    int emptyCells = 0;
    for (unsigned int i = 0; i < size; i++)
        for (unsigned int j = 0; j < size; j++)
            if (this->board->CheckLegal(j, i)) emptyCells++;

    // настройка глубины поиска в зависимости от размера
    int maxDepth = (size <= 3) ? 9 : 4;

    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            if (this->board->CheckLegal(j, i))
            {
                // проверка первого уровня ходов
                TicTacBoard* simBoard = new TicTacBoard(this->board);
                simBoard->SetCell(j, i, this->cellType);

                int moveScore = Minimax(simBoard, maxDepth, false, -1000, 1000);
                delete simBoard;

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestX = j;
                    bestY = i;
                }
            }
        }
    }

    // выполнение финального хода
    if (bestX != -1 && bestY != -1) {
        this->board->SetCell(bestX, bestY, this->cellType);
        return true;
    }

    return false;
}