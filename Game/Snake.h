#pragma once

#include "Directions.h"
#include "Constants.h"

class Snake
{
public:

	Snake();

	static sDirection GetDirection();

	static void SetDirection(sDirection dir);

	bool GetGameState();

	void SetGameState(bool state);

	int GetHeadX() const;

	void SetHeadX(int value);

	int GetHeadY() const;

	void SetHeadY(int value);

	int GetPartOfTailX(int index) const;

	void SetPartOfTailX(int index, int value);

	int GetPartOfTailY(int index) const;

	void SetPartOfTailY(int index, int value);

	int GetSnakeLength() const;

	void SetSnakeLength(int value);

private:

	int m_posX_[MAX];

	int m_posY_[MAX];

	int m_snakeLength_;

	bool m_gameOver_;

	static sDirection m_direction_;
};

