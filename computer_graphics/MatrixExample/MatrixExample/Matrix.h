#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;


template <typename Cell = double>
class Matrix
{
private:
	//int size;
	int rows, cols;
	Cell** cells;
	void AllocateCells(int, int);
	void FreeCells();

public:
	Matrix() : rows(0), cols(0), cells(nullptr) {}	// Конструктор по умолчанию
	Matrix(const Matrix&);					// Конструктор копирования
	Matrix(int, int);							// Конструктор нулевой матрицы
	Matrix(int, int, Cell*);						// Конструктор матрицы из списка
	~Matrix();								// Деструктор
	void Resize(int, int);
	void set(int x, int y) { cells[i-1][j-1] = 1; }

	Cell& operator()(int i, int j) { return cells[i - 1][j - 1]; }

	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц

	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
};


template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.rows, M.cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int rows, int cols)
{
	AllocateCells(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int rows, int cols, Cell* list)
{
	AllocateCells(rows, cols);
	for (int i = 0; i < rows; ++i)
		memcpy(cells[i], &list[i * cols], cols * sizeof(Cell));
}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if (rows != M.rows || cols != M.cols)
		this->Resize(M.rows, M.cols);
	
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	
	if (rows == M.rows && cols == M.cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (rows == M.rows && cols == M.cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				res.cells[i][j] -= M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	/*
	Matrix<Cell> res(rows, M.cols);
	try {
		if (cols == M.rows)
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < M.cols; j++)
					for (int k = 0; k < cols; k++)
						res.cells[i][j] += this->cells[i][k] * M.cells[k][j];
		else throw exception("wrong size in multipl");
	}
	catch (exception e) {
		std::cout << e.what() << std::endl;
	}


	return res;
	*/
	Matrix<Cell> res(rows, M.cols);
	if (cols == M.rows)
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < M.cols; j++)
				for (int k = 0; k < cols; k++)
					res.cells[i][j] += cells[i][k] * M.cells[k][j];

	//else
	//	if (M.rows == 1 && M.cols == 1) // åñëè â äðóãîé ìàòðèöå îäíà ÿ÷åéêà
	//		return (*this).operator*(M.cells[0][0]);

	return res;
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int rows, int cols)
{
	cells = new Cell * [rows];
	for (int i = 0; i < rows; i++)
		cells[i] = new Cell[cols];
	this->rows = rows;
	this->cols = cols;
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	//if (cells != nullptr) {
		for (int i = 0; i < rows; i++)
			delete cells[i];
		delete[] cells;
		rows = cols = 0;
	//}
}
template <typename Cell>
void Matrix<Cell>::Resize(int rows, int cols)
{
	this->FreeCells();
	this->AllocateCells(rows, cols);
}
template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i = 0; i < M.rows; i++)
		for (int j = 0; j < M.cols; j++)
			fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i = 0; i < M.rows; i++)
	{
		fo << "  ";
		for (int j = 0; j < M.cols; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

#endif MATRIX_H