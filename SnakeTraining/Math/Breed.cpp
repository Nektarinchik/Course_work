#include <algorithm>
#include <stdexcept>

#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Breed.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Rng.h"

double Breed::m_totalScore_ = 0;

std::vector<std::pair<Brain*, double>> Breed::m_scores_ = {};

Breed::Breed(const std::vector<const Snake*>& snakes)
{
    fout.open("C:\\Users\\MSI\\Desktop\\Git\\Course_work\\Game\\BestWeights.txt");
    std::ofstream localFout("BestWeights.txt");
    if (fout.fail()) {
        throw std::logic_error("file could not be opened");
    }
    m_totalScore_ = 0;
    m_scores_.clear();
    double score;
    for (int i = 0; i < snakes.size(); ++i) {
        score = snakes[i]->GetScore();
        m_scores_.push_back(std::make_pair(new Brain(snakes[i]->GetBrain()), score));
        m_totalScore_ += score;
    }
    std::sort(m_scores_.begin(), m_scores_.end(), [](auto& left, auto& right) {
        return left.second > right.second;
        });
    for (int i = 0; i < m_scores_[0].first->GetHiddenToOutput()->GetRows(); ++i) {
        for (int j = 0; j < m_scores_[0].first->GetHiddenToOutput()->GetColumns(); ++j)
            fout << m_scores_[0].first->GetHiddenToOutput()->GetElement(i, j) << " ";
        fout << "\n";
    }
    for (int i = 0; i < m_scores_[0].first->GetInputToHidden()->GetRows(); ++i) {
        for (int j = 0; j < m_scores_[0].first->GetInputToHidden()->GetColumns(); ++j)
            fout << m_scores_[0].first->GetInputToHidden()->GetElement(i, j) << " ";
        fout << "\n";
    }
    for (int i = 0; i < m_scores_[0].first->GetHiddenToOutput()->GetRows(); ++i) {
        for (int j = 0; j < m_scores_[0].first->GetHiddenToOutput()->GetColumns(); ++j)
            localFout << m_scores_[0].first->GetHiddenToOutput()->GetElement(i, j) << " ";
        localFout << "\n";
    }
    for (int i = 0; i < m_scores_[0].first->GetInputToHidden()->GetRows(); ++i) {
        for (int j = 0; j < m_scores_[0].first->GetInputToHidden()->GetColumns(); ++j)
            localFout << m_scores_[0].first->GetInputToHidden()->GetElement(i, j) << " ";
        localFout << "\n";
    }
    localFout.close();
    fout.close();
}

Brain* Breed::Spawn()
{
    return Brain::Cross(m_chooseParent_(), m_chooseParent_());
}

std::vector<Brain*> Breed::KeepTopN(int count)
{
    std::vector<Brain*> bestBrains;
    for (int i = 0; i < count; ++i) {
        bestBrains.push_back(m_scores_[i].first);
    }
    return bestBrains;
}

Brain* Breed::m_chooseParent_()
{
    double seed = Rng::GetDouble(0, m_totalScore_);
    for (auto pair : m_scores_) {
        seed -= pair.second;
        if (seed < 0)
            return pair.first;
    }
    throw std::logic_error("no matching snake found");
}
