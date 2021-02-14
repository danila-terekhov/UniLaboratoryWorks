#pragma once


#include <string>
#include <fstream>
#include "Matrix.h"
#include "AffineTransform.h"


class Model2D
{
private:
	Matrix<> Vertices;
	Matrix<int> Edges;
	Matrix<> CumulativeAT;
	Matrix<> InitialVertices;


public:


	Model2D() : Vertices(), Edges() {}
	Model2D(string, string);
	Model2D(const Matrix<> Vertices, const Matrix<int> Edges) :
		InitialVertices(Vertices), Vertices(Vertices), Edges(Edges), CumulativeAT(Identity()) {}


	Matrix<> GetVertices() { return Vertices; }
	Matrix<int> GetEdges() { return Edges; }
	double getEdge(int i, int j) { return Edges(i, j); }
	double getVertexX(int i) { return Vertices(1, i); }
	double getVertexY(int i) { return Vertices(2, i); }


	void Apply(Matrix<>);
};
Model2D::Model2D(string verticesFile, string edgesFile) : CumulativeAT(Identity()) {
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

void Model2D::Apply(Matrix<> AT)
{
	//std::cout << "XXX" << std::endl << CumulativeAT << std::endl << AT;
	CumulativeAT = AT * CumulativeAT;
	Matrix<> tmp = CumulativeAT * InitialVertices;
	std::cout << "XXX" << std::endl << CumulativeAT << std::endl << InitialVertices << std::endl << tmp;
	//std::cout << "XXX" << std::endl << InitialVertices << std::endl << CumulativeAT;
	Vertices = tmp;
}

