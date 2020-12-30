#pragma once
#include "Model2D.h"

class Model3D : public Model2D
{
	Matrix<> ProjectedVertices;
	Matrix<int> Faces;


public:
	Model3D() : Model2D(), ProjectedVertices(), Faces() {}
	Model3D(string, string);
	void setEdges(int);

	Matrix<int> getFaces() { return Faces; }
	double getVertexZ(int i) { return Vertices(3, i); }

	double getProjectedVertexX(int i) { return ProjectedVertices(1, i) / getProjectedVertexZ(i); }
	double getProjectedVertexY(int i) { return ProjectedVertices(2, i) / getProjectedVertexZ(i); }
	double getProjectedVertexZ(int i) { return ProjectedVertices(3, i); }

	void Project(Matrix<> P) { ProjectedVertices = P * Vertices; }
};


void Model3D::setEdges(int L) {

	int q, w, e;
	for (int i = 1; i < L + 1; i++) {
		// 123 = 12 / 13 / 23 
		
		q = Faces(i, 1);
		w = Faces(i, 2);
		e = Faces(i, 3);
		//Edges.cells[Faces.cells[i][0]][Faces.cells[i][1]] = 1;
		//std::cout << q << w << e << std::endl;
		Edges.set(q, w);
		Edges.set(w, q); 

		Edges.set(q, e);
		Edges.set(e, q);

		Edges.set(w, e);
		Edges.set(e, w);
		//std::cout << Edges << std::endl;
	}


		

}
Model3D::Model3D(string verticesFile, string facesFile): Model2D(verticesFile), ProjectedVertices() {
	ifstream fF(facesFile);

	int L = 0;
	string tmp;
	while (std::getline(fF, tmp))
		++L;
	fF.close();

	ifstream tmpr(facesFile);
	

	Faces.Resize(L, 3);

	tmpr >> Faces;



	setEdges(L);

}



