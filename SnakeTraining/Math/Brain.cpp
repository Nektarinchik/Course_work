#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Brain.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\CollectionsExtensions.h"

const float Brain::m_mutationChance_ = 0.02f;

Brain::Brain()
{
	m_inputToHidden_ = *Matrix::Random(m_hiddenSize_, m_inputSize_ + 1);
	m_hiddenToOutput = *Matrix::Random(m_outputSize, m_hiddenSize_ + 1);
}

Brain::Brain(Matrix* inputToHidden, Matrix* hiddenToOutput)
{
	this->m_inputToHidden_ = *inputToHidden;
	this->m_hiddenToOutput = *hiddenToOutput;
}

int Brain::GetInputSize()
{
	return m_inputSize_;
}

int Brain::GetHiddenSize()
{
	return m_hiddenSize_;
}

int Brain::GetOutputSize()
{
	return m_outputSize;
}

float Brain::GetMutationChance()
{
	return m_mutationChance_;
}

const Matrix* Brain::GetInputToHidden() const
{
	return &m_inputToHidden_;
}

const Matrix* Brain::GetHiddenToOutput() const
{
	return &m_hiddenToOutput;
}

Brain* Brain::Random()
{
	return new Brain(Matrix::Random(m_hiddenSize_, m_inputSize_ + 1), Matrix::Random(m_outputSize, m_hiddenSize_ + 1));
}

std::vector<float> Brain::Think(std::vector<float> inputs)
{
	std::vector<float> inputsWithOne = CollectionsExtensions::AttachOne(inputs, m_inputSize_);
	Matrix* inputMatrix = CollectionsExtensions::VectorToColumnMatrix(inputsWithOne, m_inputSize_ + 1);
	Matrix* hiddenMatrix = m_inputToHidden_ * *(inputMatrix);
	std::vector<float> hiddens = CollectionsExtensions::ColumnMatrixToVector(*hiddenMatrix);
	for (int i = 0; i < m_hiddenSize_; ++i) {
		ReLU(hiddens[i]);
	}
	if (inputMatrix) {
		delete inputMatrix;
		inputMatrix = nullptr;
	}
	if (hiddenMatrix) {
		delete hiddenMatrix;
		hiddenMatrix = nullptr;
	}
	std::vector<float> hiddensWithOne = CollectionsExtensions::AttachOne(hiddens, m_hiddenSize_);
	hiddenMatrix = CollectionsExtensions::VectorToColumnMatrix(hiddensWithOne, m_hiddenSize_ + 1);
	Matrix* outputMatrix = m_hiddenToOutput * *(hiddenMatrix);
	std::vector<float> outputs = CollectionsExtensions::ColumnMatrixToVector(*outputMatrix);
	if (outputMatrix) {
		delete outputMatrix;
		outputMatrix = nullptr;
	}
	if (hiddenMatrix) {
		delete hiddenMatrix;
		hiddenMatrix = nullptr;
	}
	return outputs;
}

void Brain::ReLU(float& x)
{
	if (x < 0)
		x = 0;
}

Brain* Brain::Cross(const Brain* mom, const Brain* dad)
{
	Matrix* inputToHidden = Matrix::Cross(*mom->GetInputToHidden(), *dad->GetInputToHidden(), m_mutationChance_);
	Matrix* hiddenToOutput = Matrix::Cross(*mom->GetHiddenToOutput(), *dad->GetHiddenToOutput(), m_mutationChance_);
	Brain* brain = new Brain(inputToHidden, hiddenToOutput);
	delete inputToHidden;
	delete hiddenToOutput;
	return brain;
}

Brain& Brain::operator=(const Brain& brain)
{
	this->m_inputToHidden_ = brain.m_inputToHidden_;
	this->m_hiddenToOutput = brain.m_hiddenToOutput;
	return *this;
}

Brain::~Brain() {};