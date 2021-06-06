#pragma once

#include <vector>

#include "Board.h"

class Universe
{
public:

    Universe();

    int GetWorlds();

    int GetGeneration();

    std::vector<Board*> GetBoards();

    Board* GetBoard(int index);

    const Snake* GetBestSnake();

    void Step();

    void SpawnNextGeneration();

private:

    const int m_worls_ = 100;

    const int m_keepTopN = 0;

    std::vector<Board*> m_boards_;

    int m_generation_ = 1;
};


