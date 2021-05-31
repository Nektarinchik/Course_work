#include <stdlib.h>

#include "Fruit.h"
#include "Constants.h"

Fruit::Fruit(Snake* snake)
{
	m_snake_ = snake;
	m_x_ = 0;
	m_y_ = 0;
	m_reset_ = true;
}

int Fruit::GetX()
{
	return m_x_;
}

void Fruit::SetX()
{
	m_x_ = rand() % (WINDOWSIZE_W / PIXELSIZE - 1);
	if (m_x_ == m_snake_->GetHeadX() && m_y_ == m_snake_->GetHeadY())
		SetX();
}

int Fruit::GetY()
{
	return m_y_;
}

void Fruit::SetY()
{
	m_y_ = rand() % (WINDOWSIZE_H / PIXELSIZE - 1);
	if (m_x_ == m_snake_->GetHeadX() && m_y_ == m_snake_->GetHeadY())
		SetY();
}

bool Fruit::GetReset()
{
	return m_reset_;
}

void Fruit::SetReset(bool isReset)
{
	m_reset_ = isReset;
}

Snake* Fruit::GetSnake()
{
	return m_snake_;
}
