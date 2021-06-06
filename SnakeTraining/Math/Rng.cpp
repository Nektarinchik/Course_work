#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Rng.h"

int Rng::GetInt(int min, int max)
{
	std::uniform_int_distribution<int> dis(min, max);
	return dis(Rng::m_gen_);
}

float Rng::GetFloat(float min, float max)
{
	std::uniform_real_distribution<float> dis(min, max);
	return dis(Rng::m_gen_);
}

double Rng::GetDouble(double min, double max)
{
	std::uniform_real_distribution<double> dis(min, max);
	return dis(Rng::m_gen64_);
}

std::mt19937 Rng::m_gen_{ static_cast<unsigned int>(
			   std::chrono::system_clock::now().time_since_epoch().count())
};

std::mt19937_64 Rng::m_gen64_{ static_cast<unsigned int>(
			   std::chrono::system_clock::now().time_since_epoch().count())
};