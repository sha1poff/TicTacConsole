#include "TicTacBoardMonteCarloEvaluator.h"
#include "TicTacRandomPlayer.h"


TicTacBoardMonteCarloEvaluator::TicTacBoardMonteCarloEvaluator(
	TicTacBoard* board,
	int numIterations,
	CellType startCellType,
	unsigned int xpos,
	unsigned int ypos)
{
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numVictories = 0;
	this->numLosses = 0;
	this->xpos = xpos;
	this->ypos = ypos;
	this->startCellType = startCellType;
}

TicTacBoardMonteCarloEvaluator::~TicTacBoardMonteCarloEvaluator()
{
}

void TicTacBoardMonteCarloEvaluator::EvaluateBoard()
{
	TicTacBoard* b = new TicTacBoard(this->board);
    TicTacRandomPlayer* player1 = new TicTacRandomPlayer();
    TicTacRandomPlayer* player2 = new TicTacRandomPlayer();
    TicTacRandomPlayer* currentPlayer;
    bool bGameFinished = false;

    player1->SetupPlayer("RandomX", CellType_X);
    player2->SetupPlayer("RandomO", CellType_O);
    player1->SetBoard(b);
    player2->SetBoard(b);
    currentPlayer = (this->startCellType == CellType_X) ? player1 : player2;

    // Checking already end condition!
    if (b->CheckEndCondition())
    {
        if (b->IsVictory())
            if (currentPlayer == player1)
                numLosses++;
            else
                numVictories++;
        else
            numDraws++;
        bGameFinished = true;
        return;
    }

    while (!bGameFinished)
    {
        while (!currentPlayer->MakeMove());

        if (b->CheckEndCondition())
        {
            if (b->IsVictory())
                if (currentPlayer == player1)
                    numVictories++;
                else
                    numLosses++;
            else
                numDraws++;
            bGameFinished = true;
        }
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }
}

void TicTacBoardMonteCarloEvaluator::Evaluate()
{
    for (int i = 0; i < numGames; i++)
        EvaluateBoard();
}