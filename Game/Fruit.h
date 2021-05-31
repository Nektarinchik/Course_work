#pragma once

#include "Snake.h"

class Fruit
{
public:

	Fruit(Snake* snake);

	int GetX();

	void SetX();

	int GetY();

	void SetY();

	bool GetReset();

	void SetReset(bool isReset);

	Snake* GetSnake();

private:

	Snake* m_snake_;

	bool m_reset_;

	int m_x_;

	int m_y_;
};

