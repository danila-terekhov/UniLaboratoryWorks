#include "utils.h"
#include "findEigenVectors.h"

using namespace std;

int main()
{
    std::vector<std::vector<double>> matrix;
    std::vector<double> eigenValues;
    std::vector<std::vector<double>> eigenVectors;
    unsigned int matrixDimension = 5;
    unsigned int maxEigenValues = 2;

    GenerateMatrixWithEigenValues(matrix, eigenValues, eigenVectors, matrixDimension, maxEigenValues);

    //std::cout << "matrix\n" << matrix; // << "\n\n\neigenVectors\n" << eigenVectors << "\n\n\n";

    //std::cout << "eigenValues\n";
    //for (unsigned int i = 0; i < matrixDimension; ++i)
    //{
    //    std::cout << eigenValues[i] << ' ';
    //}
    //std::cout << "\n\n\n";

    //std::vector<double> solveEigenValues(matrixDimension);
    //std::vector<std::vector<double>> solveEigenVectors;
    //unsigned int realNumberOfIteration;
    //double r;
    //findEigenVectors(matrix, 0.0000000001, 5, solveEigenVectors, realNumberOfIteration, solveEigenValues, r);

    //std::cout << "solveEigenVectors\n" << solveEigenVectors;

    //std::cout << "solveEigenValues\n";
    //for (unsigned int i = 0; i < matrixDimension; ++i)
    //{
    //    std::cout << solveEigenValues[i] << ' ';
    //}

    //unsigned int i = 1, j = 3;

    //std::cout << "\n\n\n" << leftRotationOfSymmetricMatrix(matrix, 0.5, sqrt(1 - 0.5 * 0.5), i, j);

    double zn, c, s;
    unsigned int maxRowIndex, MaxColIndex;
    findPositionAbsMaximumOutOfDiagonalElement(matrix, maxRowIndex, MaxColIndex);

    std::cout << matrix << "\n\n\n";

    zn = sqrt(matrix[maxRowIndex][maxRowIndex] * matrix[maxRowIndex][maxRowIndex]
        + matrix[maxRowIndex][MaxColIndex] * matrix[maxRowIndex][MaxColIndex]);

    c = matrix[maxRowIndex][maxRowIndex] / zn;
    s = matrix[maxRowIndex][MaxColIndex] / zn;

    std::cout << "max: " << matrix[maxRowIndex][MaxColIndex] << " c: " << c << " s: " << s << " sum: " << c * c + s * c << '\n';

    matrix = rightMultiplyMatrixByLeftRotation(matrix, c, s, maxRowIndex, MaxColIndex);

    std::cout << "tmpMatri\n" << matrix << "\n\n\n";

    //zn = sqrt(matrix[maxRowIndex][maxRowIndex] * matrix[maxRowIndex][maxRowIndex]
    //    + matrix[MaxColIndex][maxRowIndex] * matrix[MaxColIndex][maxRowIndex]);

    //c = matrix[maxRowIndex][maxRowIndex] / zn;
    //s = matrix[MaxColIndex][maxRowIndex] / zn;

    //matrix = leftMultiplyMatrixByLeftRotation(matrix, c, s, maxRowIndex, MaxColIndex);

    //std::cout << "matrix\n" << matrix << "\n\n\n";


}