#pragma once
#include <iostream>

#include "Snake.h"
#include "Brain.h"
#include "Fruit.h"

class Board
{
public:

    Board();

    Board(Brain* brain);

    Snake* GetSnake();

    void SetSnake(Snake* snake);

    Fruit* GetFruit();

    void SetFruit(Fruit* fruit);

    static bool Contains(Position pos);

    void Reset();

    ~Board();

private:

    Snake* m_snake_;

    Fruit* m_fruit_;
};
