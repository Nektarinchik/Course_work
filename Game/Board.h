#pragma once
#include <iostream>

#include "Snake.h"
#include "Fruit.h"

class Board
{
public:

    Board();

    //Board(); Ñ ÌÎÇÃÎÌ

    Snake* GetSnake();

    void SetSnake(Snake* snake);

    Fruit* GetFruit();

    void SetFruit(Fruit* fruit);

    bool Contains(std::pair<int, int> pos);

private:

    Snake* m_snake_;

    Fruit* m_fruit_;
};
