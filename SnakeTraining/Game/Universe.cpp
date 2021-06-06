#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Breed.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Universe.h"

Universe::Universe()
{
    for (int i = 0; i < m_worls_; ++i)
        m_boards_.push_back(new Board());
}

int Universe::GetWorlds()
{
    return m_worls_;
}

int Universe::GetGeneration()
{
    return m_generation_;
}

std::vector<Board*> Universe::GetBoards()
{
    return m_boards_;
}

Board* Universe::GetBoard(int index)
{
    return m_boards_[index];
}

const Snake* Universe::GetBestSnake()
{
    double score = 0;
    int maxIndex = 0;
    for (size_t i = 0; i < m_boards_.size(); ++i) {
        if (m_boards_[i]->GetSnake()->GetScore() > score) {
            score = m_boards_[i]->GetSnake()->GetScore();
            maxIndex = i;
        }
    }
    return m_boards_[maxIndex]->GetSnake();
}

void Universe::Step()
{
    for (size_t i = 0; i < m_boards_.size(); ++i) {
        m_boards_[i]->GetSnake()->Step();
    }
}

void Universe::SpawnNextGeneration()
{
    std::vector<const Snake*> snakes;
    for (size_t i = 0; i < m_boards_.size(); ++i) {
        snakes.push_back(m_boards_[i]->GetSnake());
    }
    Breed* breed = new Breed(snakes);
    m_boards_.clear();
    std::vector<Brain*> bestBrains = Breed::KeepTopN(0);
    for (size_t i = 0; i < bestBrains.size(); ++i)
        m_boards_.push_back(new Board(new Brain(*bestBrains[i])));
    for (size_t i = 0; i < m_worls_ - bestBrains.size(); ++i) {
        m_boards_.push_back(new Board(Breed::Spawn()));
    }
    ++m_generation_;
}

