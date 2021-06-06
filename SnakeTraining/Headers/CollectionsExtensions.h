#pragma once

#include <vector>

#include "Matrix.h"

class CollectionsExtensions
{
public:

    static std::vector<float> AttachOne(std::vector<float> values, int size);

    static Matrix* VectorToColumnMatrix(std::vector<float>, int size);

    static std::vector<float> ColumnMatrixToVector(const Matrix& matrix);
};

