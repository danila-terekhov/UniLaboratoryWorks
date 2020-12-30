#pragma once

#include "Camera3D.h"
#include "Model3D.h"


class Scene3D : public Camera3D
{


public:
	Model3D model;
	Scene3D(double X0, double Y0, double px, double py) : Camera3D(X0, Y0, px, py) {}

	void setModel(string vert, string faces) {
		model = Model3D(vert, faces);
		model.Project(WorldToProject);
	}

	void apply(Matrix<> AT) {
		model.Apply(AT);
		model.Project(WorldToProject);
	}


	void Render(HDC dc) {
		//HPEN pen;

		int rows = model.GetEdges().getRows();
		int cols = model.GetEdges().getCols();

		for (int i = 1; i < rows; ++i)
			for (int j = i + 1; j <= cols; ++j)
				if (model.getEdge(i, j))
				{
					MoveTo(model.getProjectedVertexX(i), model.getProjectedVertexY(i));
					LineTo(dc, model.getProjectedVertexX(j), model.getProjectedVertexY(j));
				}

		//DeleteObject(SelectObject(dc, pen));
	}
};