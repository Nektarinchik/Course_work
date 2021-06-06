#include <stdlib.h>

#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Fruit.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Constants.h"

Fruit::Fruit(Snake* snake)
{
	m_snake_ = snake;
	SetX();
	SetY();
	m_reset_ = true;
}

int Fruit::GetX()
{
	return m_x_;
}

void Fruit::SetX()
{
	m_x_ = rand() % (WINDOWSIZE_W / PIXELSIZE - 1);
	for (int i = 0; i < m_snake_->GetSnakeLength(); ++i) {
		if (m_x_ == m_snake_->GetPartOfTailX(i) && m_y_ == m_snake_->GetPartOfTailY(i))
			SetX();
	}
}

int Fruit::GetY()
{
	return m_y_;
}

void Fruit::SetY()
{
	m_y_ = rand() % (WINDOWSIZE_H / PIXELSIZE - 1);
	for (int i = 0; i < m_snake_->GetSnakeLength(); ++i) {
		if (m_x_ == m_snake_->GetPartOfTailX(i) && m_y_ == m_snake_->GetPartOfTailY(i))
			SetY();
	}
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
