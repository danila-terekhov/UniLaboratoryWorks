#include "findEigenVectors.h"

#include "utils.h"

void findEigenVectors(const std::vector<std::vector<double>>& matrix,
	const double& epsilonOffDiagonalElements,
	const unsigned int& maxNumberOfIterations,
	std::vector<std::vector<double>>& eigenVectors,
	unsigned int& realNumberOfIteration,
	std::vector<double> &eigenValues, double& r)
{
	realNumberOfIteration = 0;

	unsigned int size = matrix.size();
	eigenVectors = createIdentityMatrix(size);

	unsigned int maxRowIndex, MaxColIndex;

	std::vector<std::vector<double>> tmpMatrix = matrix;

	double zn, c, s;

	for (int i = 0; i < maxNumberOfIterations; ++i)
	{
		findPositionAbsMaximumOutOfDiagonalElement(tmpMatrix, maxRowIndex, MaxColIndex);

		if (abs(matrix[maxRowIndex][MaxColIndex]) < epsilonOffDiagonalElements)
		{
			std::cout << "break epsilonOffDiagonalElements\n";
			break;
		}
		
		zn = sqrt(tmpMatrix[maxRowIndex][maxRowIndex] * tmpMatrix[maxRowIndex][maxRowIndex]
			+ tmpMatrix[maxRowIndex][MaxColIndex] * tmpMatrix[maxRowIndex][MaxColIndex]);

		c = tmpMatrix[maxRowIndex][maxRowIndex] / zn;
		s = tmpMatrix[maxRowIndex][MaxColIndex] / zn;

		std::cout << "max: " << tmpMatrix[maxRowIndex][MaxColIndex] << " c: " << c << " s: " << s << " sum: " << c*c + s*c << '\n';

		tmpMatrix = rightMultiplyMatrixByLeftRotation(tmpMatrix, c, s, maxRowIndex, MaxColIndex);

		std::cout << "tmpMatri\n" << tmpMatrix << "\n\n\n";

		zn = sqrt(tmpMatrix[maxRowIndex][maxRowIndex] * tmpMatrix[maxRowIndex][maxRowIndex]
			+ tmpMatrix[maxRowIndex][MaxColIndex] * tmpMatrix[maxRowIndex][MaxColIndex]);

		c = tmpMatrix[maxRowIndex][maxRowIndex] / zn;
		s = tmpMatrix[maxRowIndex][MaxColIndex] / zn;

		tmpMatrix = leftMultiplyMatrixByLeftRotation(tmpMatrix, c, s, maxRowIndex, MaxColIndex);

		std::cout << "tmpMatri\n" << tmpMatrix << "\n\n\n";

		eigenVectors = leftMultiplyMatrixByLeftRotation(eigenVectors, c, s, maxRowIndex, MaxColIndex);

		std::cout << "eigenVectors\n" << eigenVectors << "\n\n\n";

		++realNumberOfIteration;
	}

	for (int i = 0; i < size; ++i)
	{
		eigenValues[i] = tmpMatrix[i][i];
	}

	eigenVectors = transposition(eigenVectors);
}
