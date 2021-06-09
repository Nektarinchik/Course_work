#include "Position.h"

std::vector<Position> Position::FourDirections = { GetPositionUp(), GetPositionRight(), GetPositionDown(), GetPositionLeft() };

std::vector<Position> Position::EightDirections = {
		GetPositionUp(), GetPositionUpRight(), GetPositionRight(), GetPositionDownRight(), GetPositionDown(),
		GetPositionDownLeft(), GetPositionLeft(), GetPositionUpLeft()
};

Position::Position(int x, int y)
{
	m_x_ = x;
	m_y_ = y;
}

int Position::GetPositionX() const
{
	return m_x_;
}

int Position::GetPositionY() const
{
	return m_y_;
}

Position Position::GetPositionUp()
{
	Position pos = Position(0, 1);
	return pos;
}

Position Position::GetPositionUpRight()
{
	Position pos = Position(1, 1);
	return pos;
}

Position Position::GetPositionRight()
{
	Position pos = Position(1, 0);
	return pos;
}

Position Position::GetPositionDownRight()
{
	Position pos = Position(1, -1);
	return pos;
}

Position Position::GetPositionDown()
{
	Position pos = Position(0, -1);
	return pos;
}

Position Position::GetPositionDownLeft()
{
	Position pos = Position(-1, -1);
	return pos;
}

Position Position::GetPositionLeft()
{
	Position pos = Position(-1, 0);
	return pos;
}

Position Position::GetPositionUpLeft()
{
	Position pos = Position(-1, 1);
	return pos;
}

Position Position::operator+(const Position& position)
{
	Position pos = Position(this->GetPositionX() + position.GetPositionX(), this->GetPositionY() + position.GetPositionY());
	return pos;
}

Position Position::operator*(int n)
{
	Position pos = Position(this->GetPositionX() * n, this->GetPositionY() * n);
	return pos;
}

bool Position::operator==(const Position& position)
{
	return this->GetPositionX() == position.GetPositionX() && this->GetPositionY() == position.GetPositionY();
}

bool Position::operator!=(const Position& position)
{
	return this->GetPositionX() != position.GetPositionX() || this->GetPositionY() != position.GetPositionY();
}