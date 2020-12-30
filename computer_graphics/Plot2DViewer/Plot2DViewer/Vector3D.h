#pragma once
#include "Matrix.h"

#define X 0
#define Y 1
#define Z 2

template <typename Cell = double>
class Vector3D : public Matrix<Cell>
{
public:
	Vector3D() : Matrix<Cell>(1, 3) {}
	Vector3D(Cell* list) : Matrix<Cell>(1, 3, list) {}
	Vector3D(const Vector3D<Cell>& V) : Matrix<Cell>(V) {}
	Vector3D(const Matrix<Cell>& M) : Matrix<Cell>(M) {}

	Cell operator() (int i) { return (i >= 0 && i <= 3) ? this->cells[0][i-1] : -1; }
	void operator() (int i, Cell data) { this->cells[0][i - 1] = data; }
	void operator() (Cell i, Cell j, Cell k) { this->cells[0][0] = i; this->cells[0][1] = j; this->cells[0][2] = k; }

	double ScalarProd(Vector3D<Cell> right) {
		double sum = 0;
		for (int i = 0; i < 3; ++i)
			sum += this->cells[0][i] * right.cells[0][i];
		return sum;
	}

	Vector3D<Cell> VectorProd(Vector3D<Cell> right) {
		Vector3D<Cell> temp;
		temp(1, this->cells[0][Y] * right.cells[0][Z] - this->cells[0][Z] * right.cells[0][Y]);
		temp(2, this->cells[0][Z] * right.cells[0][X] - this->cells[0][X] * right.cells[0][Z]);
		temp(3, this->cells[0][X] * right.cells[0][Y] - this->cells[0][Y] * right.cells[0][X]);
		return temp;
	}
	double Norm() {
		double sum = 0;
		for (int i = 0; i < 3; ++i)
			sum += this->cells[0][i] * this->cells[0][i];
		return sqrt(sum);
	}
};

