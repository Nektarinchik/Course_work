#pragma once

#include <vector>
#include <fstream>

#include "Brain.h"
#include "Snake.h"

class Breed
{
public:

    Breed(const std::vector<const Snake*>& snakes);

    static Brain* Spawn();

    static std::vector<Brain*> KeepTopN(int count);

private:

    static std::vector<std::pair<Brain*, double>> m_scores_;

    static double m_totalScore_;

    static Brain* m_chooseParent_();

    std::ofstream fout;
};



