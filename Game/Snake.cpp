#include "Snake.h"

sDirection Snake::m_direction_ = sDirection::STOP;

Snake::Snake()
{
	m_gameOver_ = false;
	m_snakeLength_ = 1;
	m_posX_[0] = WINDOWSIZE_W / PIXELSIZE / 2;
	m_posY_[0] = WINDOWSIZE_H / PIXELSIZE / 2;
}

sDirection Snake::GetDirection()
{
	return m_direction_;
}

void Snake::SetDirection(sDirection dir)
{
	m_direction_ = dir;
}

bool Snake::GetGameState()
{
	return m_gameOver_;
}

void Snake::SetGameState(bool state)
{
	m_gameOver_ = state;
}

int Snake::GetHeadX() const
{
	return m_posX_[0];
}

void Snake::SetHeadX(int value)
{
	m_posX_[0] = value;
}

int Snake::GetHeadY() const
{
	return m_posY_[0];
}

void Snake::SetHeadY(int value)
{
	m_posY_[0] = value;
}

int Snake::GetPartOfTailX(int index) const
{
	return m_posX_[index];
}

void Snake::SetPartOfTailX(int index, int value)
{
	m_posX_[index] = value;
}

int Snake::GetPartOfTailY(int index) const
{
	return m_posY_[index];
}

void Snake::SetPartOfTailY(int index, int value)
{
	m_posY_[index] = value;
}

int Snake::GetSnakeLength() const
{
	return m_snakeLength_;
}

void Snake::SetSnakeLength(int value)
{
	m_snakeLength_ = value;
}

