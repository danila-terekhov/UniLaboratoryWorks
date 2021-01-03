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
		Axes(dc);

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

	void CustomRotation(
		double x1,
		double y1,
		double z1,
		double x2,
		double y2,
		double z2,
		double phi) 
	{

		double A = x2 - x1;
		double B = y2 - y1;
		double C = z2 - z1;


		if (C) {
			double tmp = sqrt(B * B + C * C);

			apply(Translation(-x1, -y1, -z1));	

			apply(RotationX(B, -C));
			apply(RotationZ(A, -tmp));

			apply(RotationX(phi));

			apply(RotationZ(A, tmp));
			apply(RotationX(B, C));

			apply(Translation(x1, y1, z1));
		}
		else {
			apply(Translation(-x1, -y1, -z1));

			apply(RotationZ(A, -B));

			apply(RotationX(phi));

			apply(RotationZ(A, B));

			apply(Translation(x1, y1, z1));
		}


		model.Project(WorldToProject);

	}
};