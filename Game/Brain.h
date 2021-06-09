#pragma once

#include <vector>

#include "Matrix.h"

class Brain
{
public:

    Brain();

    Brain(Matrix* inputToHidden, Matrix* hiddenToOutput);

    static int GetInputSize();

    static int GetHiddenSize();

    static int GetOutputSize();

    static float GetMutationChance();

    const Matrix* GetInputToHidden() const;

    const Matrix* GetHiddenToOutput() const;

    static Brain* Random();

    static Brain* BestBrainsFromFile();

    std::vector<float> Think(std::vector<float> inputs);

    static void ReLU(float& x);

    static Brain* Cross(const Brain* mom, const Brain* dad);

    Brain& operator=(const Brain& brain);

    ~Brain();

private:

    static const int m_inputSize_ = 24;

    static const int m_hiddenSize_ = 12;

    static const int m_outputSize = 4;

    static const float m_mutationChance_;

    Matrix m_inputToHidden_;

    Matrix m_hiddenToOutput;
};