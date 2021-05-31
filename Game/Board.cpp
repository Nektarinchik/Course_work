#include "Board.h"

Board::Board()
{
	m_snake_ = new Snake();
	m_fruit_ = new Fruit(m_snake_);
}

Snake* Board::GetSnake()
{
	return m_snake_;
}

void Board::SetSnake(Snake* snake)
{
	m_snake_ = snake;
}

Fruit* Board::GetFruit()
{
	return m_fruit_;
}

void Board::SetFruit(Fruit* fruit)
{
	m_fruit_ = fruit;
}

bool Contains(std::pair<int, int> pos)
{
	return pos.first >= 0 && pos.second >= 0 && pos.first < WINDOWSIZE_W / PIXELSIZE && pos.second < WINDOWSIZE_H / PIXELSIZE;
}
