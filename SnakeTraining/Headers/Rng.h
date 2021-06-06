#pragma once

#include <chrono>
#include <random>

class Rng
{
public:

    static int GetInt(int min, int max);

    static float GetFloat(float min, float max);

    static double GetDouble(double min, double max);

private:

    static std::mt19937 m_gen_;

    static std::mt19937_64 m_gen64_;
};

