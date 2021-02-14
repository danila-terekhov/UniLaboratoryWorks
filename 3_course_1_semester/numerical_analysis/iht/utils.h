#pragma once

#include <vector>
#include <iostream>

std::vector<std::vector<double>> leftRotationOfSymmetricMatrix(const std::vector<std::vector<double>>& matrix,
	const double& c, const double& s,
	unsigned int& i, unsigned int& j);

// умножить слева симметричную матрицу на левое вращение
std::vector<std::vector<double>> leftMultiplyMatrixByLeftRotation(const std::vector<std::vector<double>>& matrix,
	const double& c, const double& s,
	unsigned int& i, unsigned int& j);

// умножить справа симметричную матрицу на левое вращение
std::vector<std::vector<double>> rightMultiplyMatrixByLeftRotation(const std::vector<std::vector<double>>& matrix,
	const double& c, const double& s,
	unsigned int& i, unsigned int& j);

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<double>>& matrix);

std::vector<std::vector<double>> operator*(const std::vector<std::vector<double>>& matrix1,
	const std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> operator+(const std::vector<std::vector<double>>& matrix1,
	const std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> operator-(const std::vector<std::vector<double>>& matrix1,
	const std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> operator*(const std::vector<std::vector<double>>& matrix, const double& k);
std::vector<std::vector<double>> operator*(const double& k, const std::vector<std::vector<double>>& matrix);

std::vector<double> randomVector(const unsigned int& size, const unsigned int& maxValue);

std::vector<std::vector<double>> createDiagonalMatrix(const std::vector<double>& vector);

std::vector<std::vector<double>> createIdentityMatrix(const unsigned int& size);

std::vector<std::vector<double>> createRandomMatrix(const unsigned int& sizeRow, const unsigned int& sizeCol);

std::vector<std::vector<double>> transposition(const std::vector<std::vector<double>>& matrix);

// наверное тупо нормализировать матрицу, но тут это используется один раз и для матрицы 1хN
std::vector<std::vector<double>> normalize(const std::vector<std::vector<double>>& matrix);

void findPositionAbsMaximumOutOfDiagonalElement(const std::vector<std::vector<double>>& matrix,
	unsigned int& rowIndex, unsigned int& colIndex);

void GenerateMatrixWithEigenValues(std::vector<std::vector<double>>& matrix,
    std::vector<double>& eigenValues,
    std::vector<std::vector<double>>& eigenVectors,
    const unsigned int& matrixDimension,
    const unsigned int& maxEigenValues);