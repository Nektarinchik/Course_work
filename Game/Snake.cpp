#include <cmath>
#include <algorithm>
#include <string.h>
#include <string>

#include "Snake.h"
#include "Board.h"

Snake::Snake()
{
	m_direction_ = sDirection::STOP;
	m_gameOver_ = false;
	m_snakeLength_ = m_initialLength_;
	m_score_ = 0;
	m_lifeTime_ = 0;
	m_fruits_ = 0;
	m_posX_[0] = rand() % (WINDOWSIZE_W / PIXELSIZE - 1);
	m_posY_[0] = rand() % (WINDOWSIZE_H / PIXELSIZE - 1);
	for (int i = 1; i < m_initialLength_; ++i) {
		m_posX_[i] = m_posX_[0];
		m_posY_[i] = m_posY_[0];
	}
	m_board_ = nullptr;
	m_brain_ = nullptr;
	m_timeRemaining_ = m_initialTimeRemainig_;
}

Snake::Snake(Board* board)
{
	m_direction_ = sDirection::STOP;
	m_gameOver_ = false;
	m_snakeLength_ = m_initialLength_;
	m_score_ = 0;
	m_lifeTime_ = 0;
	m_fruits_ = 0;
	m_posX_[0] = rand() % (WINDOWSIZE_W / PIXELSIZE - 1);
	m_posY_[0] = rand() % (WINDOWSIZE_H / PIXELSIZE - 1);
	for (int i = 1; i < m_initialLength_; ++i) {
		m_posX_[i] = m_posX_[0];
		m_posY_[i] = m_posY_[0];
	}
	m_board_ = board;
	m_brain_ = Brain::BestBrainsFromFile();
	m_timeRemaining_ = m_initialTimeRemainig_;
}

Snake::Snake(Board* board, Brain* brain)
{
	m_direction_ = sDirection::STOP;
	m_gameOver_ = false;
	m_snakeLength_ = m_initialLength_;
	m_score_ = 0;
	m_lifeTime_ = 0;
	m_fruits_ = 0;
	m_posX_[0] = rand() % (WINDOWSIZE_W / PIXELSIZE - 1);
	m_posY_[0] = rand() % (WINDOWSIZE_H / PIXELSIZE - 1);
	for (int i = 1; i < m_initialLength_; ++i) {
		m_posX_[i] = m_posX_[0];
		m_posY_[i] = m_posY_[0];
	}
	m_board_ = board;
	m_brain_ = brain;
	m_timeRemaining_ = m_initialTimeRemainig_;
}

void Snake::Step()
{
	if (!m_gameOver_) {
		std::vector<float> observations = m_gatherObservations_();
		std::vector<float> actions = m_brain_->Think(observations);
		int maxIndex = 0;
		for (int i = 0; i < Brain::GetOutputSize(); i++)
			if (actions[i] > actions[maxIndex])
				maxIndex = i;
		switch (maxIndex) {
		case 0:
			SetDirection(sDirection::UP);
			break;
		case 1:
			SetDirection(sDirection::RIGHT);
			break;
		case 2:
			SetDirection(sDirection::DOWN);
			break;
		case 3:
			SetDirection(sDirection::LEFT);
			break;
		}
	}
}

std::string Snake::Report() const
{
	return "Life time: " + std::to_string(m_lifeTime_) + "\r\nLeft: "
		+ std::to_string(m_timeRemaining_) + "\r\nFruits: " + std::to_string(m_fruits_)
		+ "\r\nPoints: " + std::to_string(GetScore());
}

sDirection Snake::GetDirection() const
{
	return m_direction_;
}

void Snake::SetDirection(sDirection dir)
{
	m_direction_ = dir;
}

bool Snake::Contains(Position pos)
{
	for (int i = 1; i < m_snakeLength_; ++i) {
		if (m_posX_[i] == pos.GetPositionX() && m_posY_[i] == pos.GetPositionY())
			return true;
	}
	return false;
}

bool Snake::GetGameState() const
{
	return m_gameOver_;
}

void Snake::SetGameState(bool state)
{
	m_gameOver_ = state;
}

int Snake::GetBonusPerApple() const
{
	return m_bonusTimePerApple_;
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

int Snake::GetLifeTime() const
{
	return m_lifeTime_;
}

void Snake::SetLifeTime(int value)
{
	m_lifeTime_ = value;
	ResetScore();
}

int Snake::GetFruits() const
{
	return m_fruits_;
}

void Snake::SetFruits(int value)
{
	m_fruits_ = value;
	ResetScore();
}

int Snake::GetTimeRemaining() const
{
	return m_timeRemaining_;
}

void Snake::SetTimeRemaining(int value)
{
	m_timeRemaining_ = value;
}

double Snake::GetScore() const
{
	return m_score_;
}

void Snake::ResetScore()
{
	m_score_ = static_cast<double>(m_lifeTime_ * m_lifeTime_ * pow(2, std::min(m_fruits_, 10)) * std::max(1, m_fruits_ - 9));
}


Board Snake::GetBoard() const
{
	return *m_board_;
}

Brain Snake::GetBrain() const
{
	return *m_brain_;
}

Snake::~Snake()
{
	if (m_brain_) {
		delete m_brain_;
		m_brain_ = nullptr;
	}
}

std::vector<float> Snake::m_gatherObservations_()
{
	std::vector<float> observations;
	for (size_t i = 0; i < Position::EightDirections.size(); ++i) {
		observations.push_back(m_inverseDistanceToWall_(Position::EightDirections[i]));
		observations.push_back(m_inverseDistanceToApple_(Position::EightDirections[i]));
		observations.push_back(m_inverseDistanceToTail_(Position::EightDirections[i]));
	}
	return observations;
}

float Snake::m_inverseDistanceToWall_(Position dir)
{
	Position head = Position(this->m_posX_[0], this->m_posY_[0]);
	for (int i = 1; true; ++i) {
		if (!Board::Contains(dir * i + head))
			return 1.0f / i;
	}
}

float Snake::m_inverseDistanceToApple_(Position dir)
{
	Position head = Position(this->m_posX_[0], this->m_posY_[0]);
	Position fruit = Position(m_board_->GetFruit()->GetX(), m_board_->GetFruit()->GetY());
	for (int i = 1; true; ++i) {
		if (!Board::Contains(dir * i + head))
			return 0;
		else if (fruit == dir * i + head)
			return 1.0f / i;
	}
}

float Snake::m_inverseDistanceToTail_(Position dir)
{
	Position head = Position(this->m_posX_[0], this->m_posY_[0]);
	for (int i = 1; true; ++i) {
		if (!Board::Contains(dir * i + head))
			return 0;
		else if (Contains(head + dir * i))
			return 1.0f / i;
	}
}

Snake& Snake::operator=(const Snake& snake)
{
	for (int i = 0; i < snake.m_snakeLength_; ++i) {
		m_posX_[i] = snake.m_posX_[i];
		m_posY_[i] = snake.m_posY_[i];
	}
	m_snakeLength_ = snake.m_snakeLength_;
	m_gameOver_ = snake.m_gameOver_;
	m_lifeTime_ = snake.m_lifeTime_;
	m_fruits_ = snake.m_fruits_;
	m_timeRemaining_ = snake.m_timeRemaining_;
	m_score_ = snake.m_score_;
	m_direction_ = snake.m_direction_;
	m_board_ = new Board(*snake.m_board_);
	if (m_brain_) {
		delete m_brain_;
		m_brain_ = nullptr;
	}
	m_brain_ = new Brain(*snake.m_brain_);
	return *this;
}
