#include <iostream>

#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\CollectionsExtensions.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Brain.h"

std::vector<float> CollectionsExtensions::AttachOne(std::vector<float> values, int size)
{
	std::vector<float> valuesWithOne;
	for (int i = 0; i < size; ++i) {
		valuesWithOne.push_back(values[i]);
	}
	valuesWithOne.push_back(1.0);
	return valuesWithOne;
}

Matrix* CollectionsExtensions::VectorToColumnMatrix(std::vector<float> vector, int size)
{
	float** columnArr = new float* [size];
	if (!columnArr) {
		throw std::out_of_range("not enough memory");
		exit(1);
	}
	for (int i = 0; i < size; ++i) {
		columnArr[i] = new float[1];
		if (!columnArr[i]) {
			throw std::out_of_range("not enough memory");
			exit(1);
		}
	}
	for (int i = 0; i < size; ++i) {
		columnArr[i][0] = vector[i];
	}
	return new Matrix(columnArr, size, 1);
}

std::vector<float> CollectionsExtensions::ColumnMatrixToVector(const Matrix& matrix)
{
	int size = matrix.GetRows();
	std::vector<float> vector;
	for (int i = 0; i < size; ++i) {
		vector.push_back(matrix.GetElement(i, 0));
	}
	return vector;
}
