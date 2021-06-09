#pragma once

#include <string>
#include <vector>

#include "Directions.h"
#include "Constants.h"
#include "Position.h"

class Board;

class Brain;

class Snake
{
public:

    Snake();

    Snake(Board* board);

    Snake(Board* board, Brain* brain);

    void Step();

    std::string Report() const;

    sDirection GetDirection() const;

    void SetDirection(sDirection dir);

    bool Contains(Position pos);

    bool GetGameState() const;

    void SetGameState(bool state);

    int GetBonusPerApple() const;

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

    int GetLifeTime() const;

    void SetLifeTime(int value);

    int GetFruits() const;

    void SetFruits(int value);

    int GetTimeRemaining() const;

    void SetTimeRemaining(int value);

    double GetScore() const;

    void ResetScore();

    Board GetBoard() const;

    Brain GetBrain() const;

    Snake& operator=(const Snake& snake);

    ~Snake();

private:

    int m_posX_[MAX];

    int m_posY_[MAX];

    int m_snakeLength_;

    bool m_gameOver_;

    const int m_initialLength_ = 6;

    const int m_initialTimeRemainig_ = 200;

    const int m_bonusTimePerApple_ = 100;

    int m_lifeTime_;

    int m_fruits_;

    int m_timeRemaining_;

    double m_score_;

    Board* m_board_;

    Brain* m_brain_;

    sDirection m_direction_;

    std::vector<float> m_gatherObservations_();

    float m_inverseDistanceToWall_(Position dir);

    float m_inverseDistanceToApple_(Position dir);

    float m_inverseDistanceToTail_(Position dir);
};