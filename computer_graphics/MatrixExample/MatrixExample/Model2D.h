#pragma once

#include <string>
#include <fstream>
#include "Matrix.h"
#include "AffineTransform.h"


class Model2D 
{
protected:
	Matrix<> Vertices;
	Matrix<int> Edges;
	Matrix<> CumulativeAT;
	Matrix<> InitialVertices;

public:

	Model2D() : Vertices(), Edges() {}
	Model2D(string, string);
	Model2D(string);
	Model2D(const Matrix<> Vertices, const Matrix<int> Edges):
		InitialVertices(Vertices), Vertices(Vertices), Edges(Edges), CumulativeAT(Identity()) {}


	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }
	double getVertexX(int i) { return Vertices(1, i); }
	double getVertexY(int i) { return Vertices(2, i); }


	void Apply(Matrix<>);
};
Model2D::Model2D(string verticesFile, string edgesFile): CumulativeAT(Identity()) {
	ifstream vF(verticesFile), eF(edgesFile);
	
	string s;
	getline(vF, s);
	int M = std::count(s.begin(), s.end(), ' ') + 1;
	vF.seekg(0);

	Vertices.Resize(3, M);
	Edges.Resize(M, M);

	vF >> Vertices;
	InitialVertices = Vertices;
	eF >> Edges;

	vF.close();
	eF.close();

}
Model2D::Model2D(string verticesFile) : CumulativeAT(Identity3D()) {
	ifstream vF(verticesFile);

	string s;
	getline(vF, s);
	int M = std::count(s.begin(), s.end(), ' ') + 1;
	vF.seekg(0);

	Vertices.Resize(4, M);
	Edges.Resize(M, M);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			Edges.cells[i][j] = 0;

	vF >> Vertices;
	InitialVertices = Vertices;

	vF.close();
}
void Model2D::Apply(Matrix<> AT)
{
//std::cout << "XXX" << std::endl << CumulativeAT << std::endl << AT;
	CumulativeAT = AT * CumulativeAT;
	Matrix<> tmp = CumulativeAT * InitialVertices;
	std::cout << "XXX" << std::endl << CumulativeAT << std::endl << InitialVertices << std::endl << tmp;
//std::cout << "XXX" << std::endl << InitialVertices << std::endl << CumulativeAT;
	Vertices = tmp;
}

