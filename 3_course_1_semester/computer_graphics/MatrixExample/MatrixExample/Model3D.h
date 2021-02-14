#pragma once

#include "Model2D.h"

class Model3D : public Model2D
{
	Matrix<> ProjectedVertices;
	Matrix<int> Faces;
	void setEdges(int);

public: 
	Model3D() : Model2D(), ProjectedVertices(), Faces() {}
	Model3D(string, string);

	Matrix<int> getFaces() { return Faces; }
	double getVertexZ(int i) { return Vertices(3, i); }

	double getProjectedVertexX(int i) { return ProjectedVertices(1, i) / getProjectedVertexZ(i); }
	double getProjectedVertexY(int i) { return ProjectedVertices(2, i) / getProjectedVertexZ(i); }
	double getProjectedVertexZ(int i) { return ProjectedVertices(3, i); }

	void Project(Matrix<> P) { ProjectedVertices = P * Vertices; }
};

void Model3D::setEdges(int L) {
	Edges.Resize(L, L);

	for (int i = 1; i < L+1; i++) {
		// 123 = 12 / 13 / 23 
		int q, w, e;
		q = Faces(i, 1);
		w = Faces(i, 2);
		e = Faces(i, 3);

		Faces.set(q, w);
		Faces.set(q, e);
		Faces.set(w, e);
		
	}




}
Model3D::Model3D(string verticesFile, string facesFile): Model2D(verticesFile) {
	ifstream fF(facesFile);

	int L = 0;
	while (!fF.eof()) {
		getline(fF, (string)nullptr);
		L++;
	}
	fF.seekg(0);

	Faces.Resize(L, 3);

	fF >> Faces;

	fF.close();

	setEdges(L);

}



