#include "utils.h"

std::vector<std::vector<double>> leftRotationOfSymmetricMatrix(const std::vector<std::vector<double>>& matrix,
    const double& c, const double& s,
    unsigned int& i, unsigned int& j)
{
    std::vector<std::vector<double>> matrix2 = leftMultiplyMatrixByLeftRotation(matrix, c, s, i, j);

    std::cout << "matrix2:\n" << matrix2 << "\n\n";

    std::vector<std::vector<double>> matrix3 = rightMultiplyMatrixByLeftRotation(matrix2, c, s, i, j);

    std::cout << "matrix3:\n" << matrix3 << "\n\n";

    return matrix3;
}

std::vector<std::vector<double>> leftMultiplyMatrixByLeftRotation(const std::vector<std::vector<double>>& matrix,
    const double& c, const double& s, unsigned int& i, unsigned int& j)
{
    unsigned int size = matrix.size();

    std::vector<std::vector<double>> result = matrix;

    for (unsigned int m = 0; m < size; ++m)
    {
        result[i][m] = c * matrix[i][m] + s * matrix[j][m];
        // preResult[m][i] = preResult[i][m];
        result[j][m] = -s * matrix[i][m] + c * matrix[j][m];
        // preResult[m][j] = preResult[j][m];
    }

    return result;
}

std::vector<std::vector<double>> rightMultiplyMatrixByLeftRotation(const std::vector<std::vector<double>>& matrix,
    const double& c, const double& s, unsigned int& i, unsigned int& j)
{
    unsigned int size = matrix.size();

    std::vector<std::vector<double>> result = matrix;

    for (unsigned int l = 0; l < size; ++l)
    {
        result[l][i] = c * matrix[l][i] + s * matrix[l][j];
        // preResult[m][i] = preResult[i][m];
        result[l][j] = -s * matrix[l][i] + c * matrix[l][j];
        // preResult[m][j] = preResult[j][m];
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<double>>& matrix)
{
    unsigned int size = matrix.size();
    
    for (unsigned int i = 0; i < size; ++i)
    {
        for (unsigned int j = 0; j < matrix[i].size(); ++j)
        {
            out.width(9);
            out << matrix[i][j] << ' ';
        }
        
        out << '\n';
    }

    return out;
}

std::vector<std::vector<double>> operator*(const std::vector<std::vector<double>>& matrix1,
    const std::vector<std::vector<double>>& matrix2)
{
    unsigned int sizeROW1 = matrix1.size();
    unsigned int sizeCOL1 = matrix1[0].size();

    std::vector<std::vector<double>> result(sizeROW1);

    for (unsigned int i = 0; i < sizeROW1; i++)
    {
        result[i].resize(sizeROW1);
        for (unsigned int j = 0; j < sizeROW1; j++)
        {
            result[i][j] = 0;
            for (unsigned int k = 0; k < sizeCOL1; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

std::vector<std::vector<double>> operator+(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2)
{
    unsigned int sizeRow = matrix1.size();
    unsigned int sizeCol = matrix1[0].size();

    std::vector<std::vector<double>> result(sizeRow);

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        result[i].resize(sizeCol);
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>> operator-(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2)
{
    return (matrix1 + (-1) * matrix2);
}

std::vector<std::vector<double>> operator*(const std::vector<std::vector<double>>& matrix, const double& k)
{
    unsigned int sizeRow = matrix.size();
    unsigned int sizeCol = matrix[0].size();

    std::vector<std::vector<double>> result(sizeRow);

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        result[i].resize(sizeCol);
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            result[i][j] = matrix[i][j] * k;
        }
    }
    return result;
}

std::vector<std::vector<double>> operator*(const double& k, const std::vector<std::vector<double>>& matrix)
{
    return matrix * k;
}

std::vector<double> randomVector(const unsigned int& size, const unsigned int& maxValue)
{
    std::vector<double> result(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        result[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (static_cast<double>(maxValue) + maxValue) - maxValue;
    }

    return result;
}

std::vector<std::vector<double>> createDiagonalMatrix(const std::vector<double>& vector)
{
    unsigned int size = vector.size();

    std::vector<std::vector<double>> result(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        result[i].resize(size);
        for (unsigned int j = 0; j < size; ++j)
        {
            result[i][j] = 0;
        }
        result[i][i] = vector[i];
    }

    return result;
}

std::vector<std::vector<double>> createIdentityMatrix(const unsigned int& size)
{
    std::vector<std::vector<double>> matrix(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        matrix[i].resize(size);
        for (unsigned int j = 0; j < size; ++j)
        {
            matrix[i][j] = 0;
        }
        matrix[i][i] = 1;
    }

    return matrix;
}

std::vector<std::vector<double>> createRandomMatrix(const unsigned int& sizeRow, const unsigned int& sizeCol)
{
    std::vector<std::vector<double>> result(sizeRow);

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        result[i].resize(sizeCol);
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            result[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        }
    }
    return result;
}

std::vector<std::vector<double>> transposition(const std::vector<std::vector<double>>& matrix)
{
    unsigned int sizeRow = matrix.size();
    unsigned int sizeCol = matrix[0].size();

    std::vector<std::vector<double>> result(sizeCol);

    for (unsigned int i = 0; i < sizeCol; ++i)
    {
        result[i].resize(sizeRow);
    }

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>> normalize(const std::vector<std::vector<double>>& matrix)
{
    std::vector<std::vector<double>> result = matrix;

    unsigned int sizeRow = matrix.size();
    unsigned int sizeCol = matrix[0].size();

    double sum = 0;

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            sum += result[i][j] * result[i][j];
        }
    }

    return result * (1 / sqrt(sum));
}

void findPositionAbsMaximumOutOfDiagonalElement(const std::vector<std::vector<double>>& matrix,
    unsigned int& rowIndex, unsigned int& colIndex)
{
    unsigned int rowSize = matrix.size();
    unsigned int colSize = matrix[0].size();

    unsigned int maxRowIndex = 0, maxColIndex = 1;

    for (int i = 0; i < rowSize; ++i)
    {
        for (int j = 0; j < colSize; ++j)
        {
            if (i == j)
            {
                continue;
            }

            if (abs(matrix[i][j]) > abs(matrix[maxRowIndex][maxColIndex]))
            {
                maxRowIndex = i;
                maxColIndex = j;
            }
        }
    }

    rowIndex = maxRowIndex;
    colIndex = maxColIndex;
}

void GenerateMatrixWithEigenValues(std::vector<std::vector<double>>& matrix,
    std::vector<double>& eigenValues,
    std::vector<std::vector<double>>& eigenVectors,
    const unsigned int& matrixDimension,
    const unsigned int& maxEigenValues)
{
    eigenValues = randomVector(matrixDimension, maxEigenValues);

    std::vector<std::vector<double>> DiagonalMatrix = createDiagonalMatrix(eigenValues);

    std::vector<std::vector<double>> IdentityMatrix = createIdentityMatrix(matrixDimension);

    std::vector<std::vector<double>> w = createRandomMatrix(matrixDimension, 1);
    w = normalize(w);

    std::vector<std::vector<double>> H = IdentityMatrix - 2 * w * transposition(w);
    std::vector<std::vector<double>> HT = transposition(H);
    eigenVectors = HT;
    matrix = H * DiagonalMatrix * HT;
}
