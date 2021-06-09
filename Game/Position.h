#pragma once

#include <vector>

class Position
{
public:

    Position(int x, int y);

    int GetPositionX() const;

    int GetPositionY() const;

    static Position GetPositionUp();

    static Position GetPositionUpRight();

    static Position GetPositionRight();

    static Position GetPositionDownRight();

    static Position GetPositionDown();

    static Position GetPositionDownLeft();

    static Position GetPositionLeft();

    static Position GetPositionUpLeft();

    Position operator+(const Position& position);

    Position operator*(int n);

    bool operator==(const Position& position);

    bool operator!=(const Position& position);

    static std::vector<Position> FourDirections;

    static std::vector<Position> EightDirections;

private:

    int m_x_;

    int m_y_;
};


