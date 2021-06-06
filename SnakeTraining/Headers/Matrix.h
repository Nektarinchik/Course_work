#pragma once

class Matrix
{
public:

    Matrix();

    Matrix(int rows, int cols);

    Matrix(float** cells, int rows, int cols);

    static Matrix* Random(int rows, int cols);

    int GetRows() const;

    int GetColumns() const;

    float GetElement(int i, int j) const;

    void SetElement(int i, int j, float value);

    Matrix* operator*(const Matrix& matrix);

    Matrix& operator=(const Matrix& matrix);

    static Matrix* Cross(const Matrix& mom, const Matrix& dad, float mutationChance);

    ~Matrix();

private:

    int m_rows_;

    int m_columns_;

    float** m_cells_;
};

