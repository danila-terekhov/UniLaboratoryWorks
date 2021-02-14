#pragma once

#include <vector>

void findEigenVectors(const std::vector<std::vector<double>>& matrix,
	const double& epsilonOffDiagonalElements,
	const unsigned int& maxNumberOfIterations,
	std::vector<std::vector<double>>& eigenVectors,
	unsigned int& realNumberOfIteration,
	std::vector<double> &eigenValues,
	double &r);