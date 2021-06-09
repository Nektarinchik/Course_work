#include "Board.h"

Board::Board()
{
	m_snake_ = new Snake(this);
	m_fruit_ = new Fruit(m_snake_);
}

Board::Board(Brain* brain)
{
	m_snake_ = new Snake(this, brain);
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

bool Board::Contains(Position pos)
{
	return pos.GetPositionX() >= 0
		&& pos.GetPositionY() >= 0
		&& pos.GetPositionX() < WINDOWSIZE_W / PIXELSIZE
		&& pos.GetPositionY() < WINDOWSIZE_H / PIXELSIZE;
}

void Board::Reset()
{
	if (m_snake_) {
		delete m_snake_;
		m_snake_ = nullptr;
	}
	if (m_fruit_) {
		delete m_fruit_;
		m_fruit_ = nullptr;
	}
	m_snake_ = new Snake(this);
	m_fruit_ = new Fruit(m_snake_);
}

Board::~Board()
{
	if (m_fruit_) {
		delete m_fruit_;
		m_fruit_ = nullptr;
	}
	if (m_snake_) {
		delete m_snake_;
		m_snake_ = nullptr;
	}
}
