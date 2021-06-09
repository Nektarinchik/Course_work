#pragma warning(suppress : 117)

#include <iostream>

#include "Matrix.h"
#include "Rng.h"

std::ifstream Matrix::fin("BestBrains.txt");

Matrix::Matrix()
{
	m_rows_ = 0;
	m_columns_ = 0;
	m_cells_ = nullptr;
}

Matrix::Matrix(int rows, int cols)
{
	m_rows_ = rows;
	m_columns_ = cols;
	m_cells_ = new float* [m_rows_];
	if (!m_cells_) {
		throw std::out_of_range("not enough memory");
		exit(1);
	}
	for (int i = 0; i < m_rows_; ++i) {
		m_cells_[i] = new float[m_columns_];
		if (!m_cells_[i]) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
	}
	for (int i = 0; i < m_rows_; ++i) {
		for (int j = 0; j < m_columns_; ++j) {
			m_cells_[i][j] = 0;
		}
	}
}

Matrix::Matrix(float** cells, int rows, int cols)
{
	m_rows_ = rows;
	m_columns_ = cols;
	m_cells_ = new float* [m_rows_];
	if (!m_cells_) {
		throw std::out_of_range("not enough memory");
		exit(1);
	}
	for (int i = 0; i < m_rows_; ++i) {
		m_cells_[i] = new float[m_columns_];
		if (!m_cells_[i]) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
	}
	for (int i = 0; i < m_rows_; ++i) {
		for (int j = 0; j < m_columns_; ++j) {
			m_cells_[i][j] = cells[i][j];
		}
	}
	for (int i = 0; i < m_rows_; ++i) {
		if (cells[i]) {
			delete[] cells[i];
			cells[i] = nullptr;
		}
	}
	if (cells) {
		delete[] cells;
		cells = nullptr;
	}
}

Matrix* Matrix::Random(int rows, int cols)
{
	float** cells = new float* [rows];
	if (!cells) {
		throw std::out_of_range("not enough memory");
		exit(1);
	}
	for (int i = 0; i < rows; ++i) {
		cells[i] = new float[cols];
		if (!cells[i]) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
	}
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cells[i][j] = Rng::GetFloat(-1.0, 1.0);
		}
	}
	return new Matrix(cells, rows, cols);
}

Matrix* Matrix::BestBrainsFromFile(int rows, int cols)
{
	float** cells = new float* [rows];
	if (!cells) {
		throw std::out_of_range("not enough memory");
		exit(1);
	}
	for (int i = 0; i < rows; ++i) {
		cells[i] = new float[cols];
		if (!cells[i]) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
	}
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			fin >> cells[i][j];
		}
	}
	return new Matrix(cells, rows, cols);
}

int Matrix::GetRows() const
{
	return m_rows_;
}

int Matrix::GetColumns() const
{
	return m_columns_;
}

float Matrix::GetElement(int i, int j) const
{
	return m_cells_[i][j];
}

void Matrix::SetElement(int i, int j, float value)
{
	m_cells_[i][j] = value;
}

Matrix* Matrix::operator*(const Matrix& matrix)
{
	if (this->m_columns_ != matrix.GetRows())
		throw std::invalid_argument("the dimensions don't match");
	float** newArray = new float* [this->m_rows_];
	if (!newArray) {
		throw std::out_of_range("not enough memory");
		exit(1);
	}
	for (int i = 0; i < this->m_rows_; ++i) {
		newArray[i] = new float[matrix.GetColumns()];
		if (!newArray[i]) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
	}
	float sum;
	for (int i = 0; i < this->m_rows_; ++i) {
		for (int j = 0; j < matrix.GetColumns(); ++j) {
			sum = 0;
			for (int k = 0; k < this->m_columns_; ++k)
				sum += this->m_cells_[i][k] * matrix.GetElement(k, j);
			newArray[i][j] = sum;
		}
	}
	return new Matrix(newArray, this->m_rows_, matrix.m_columns_);
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
	if (this == &matrix) {
		return *this;
	}
	int oldRows = m_rows_;
	int oldColumns = m_columns_;
	m_rows_ = matrix.GetRows();
	m_columns_ = matrix.GetColumns();
	if (!m_cells_) {
		m_cells_ = new float* [m_rows_];
		if (!m_cells_) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
		for (int i = 0; i < m_rows_; ++i) {
			m_cells_[i] = new float[m_columns_];
			if (!m_cells_[i]) {
				throw std::out_of_range("not enough memory");
				exit(1);
			}
		}
	}
	else {
		for (int i = 0; i < oldRows; ++i) {
			if (m_cells_[i]) {
				delete[] m_cells_[i];
				m_cells_[i] = nullptr;
			}
		}
		if (m_cells_) {
			delete[] m_cells_;
			m_cells_ = nullptr;
		}
		m_cells_ = new float* [m_rows_];
		if (!m_cells_) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
		for (int i = 0; i < m_rows_; ++i) {
			m_cells_[i] = new float[m_columns_];
			if (!m_cells_[i]) {
				throw std::out_of_range("not enough memory");
				exit(1);
			}
		}
	}
	for (int i = 0; i < m_rows_; ++i) {
		for (int j = 0; j < m_columns_; ++j) {
			m_cells_[i][j] = matrix.GetElement(i, j);
		}
	}
	return *this;
}

Matrix* Matrix::Cross(const Matrix& mom, const Matrix& dad, float mutationChance)
{
	if (mom.m_rows_ != dad.m_rows_ || mom.m_columns_ != dad.m_columns_)
		throw std::invalid_argument("the dimensions don't match");
	float** cells = new float* [mom.m_rows_];
	if (!cells) {
		throw std::out_of_range("not enough memory");
		exit(1);
	}
	for (int i = 0; i < mom.m_rows_; ++i) {
		cells[i] = new float[mom.m_columns_];
		if (!cells[i]) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
	}
	for (int i = 0; i < mom.m_rows_; ++i) {
		for (int j = 0; j < mom.m_columns_; ++j) {
			if (Rng::GetFloat(0.0f, 1.0f) < 0.5f)
				cells[i][j] = mom.m_cells_[i][j];
			else
				cells[i][j] = dad.m_cells_[i][j];
			if (Rng::GetFloat(0.0f, 1.0f) < mutationChance)
				cells[i][j] = Rng::GetFloat(-1.0f, 1.0f);
		}
	}
	return new Matrix(cells, mom.m_rows_, mom.m_columns_);
}


Matrix::~Matrix()
{
	fin.close();
	for (int i = 0; i < m_rows_; ++i) {
		if (m_cells_[i]) {
			delete[] m_cells_[i];
			m_cells_[i] = nullptr;
		}
	}
	if (m_cells_) {
		delete[] m_cells_;
		m_cells_ = nullptr;
	}
}
