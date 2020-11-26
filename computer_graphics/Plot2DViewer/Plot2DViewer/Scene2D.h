#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include "Matrix.h"
#include "Model2D.h"
#include <cmath>

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
	Model2D model;
public:
	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
	}
	void setModel(string vert, string edg) {
		model = Model2D(vert, edg);
	}
	void Render(HDC dc, bool axes = true) {
		HPEN pen;
		if (axes)
			Axes(dc);




		int rows = model.GetEdges().getRows();
		int cols = model.GetEdges().getCols();

		for (int i = 1; i < rows; ++i)
			for (int j = i + 1; j <= cols; ++j)
				if (model.getEdge(i, j))
				{
					MoveTo(model.getVertexX(i), model.getVertexY(i));
					LineTo(dc, model.getVertexX(j), model.getVertexY(j));
				}

		DeleteObject(SelectObject(dc, pen));
	}
	void apply(Matrix<double> A) {
		model.Apply(A);
	}
	
	void Plot(HDC dc, Func f, bool axes = true)
	{
		if (axes)
			Axes(dc);

		double h = 1/px;
		//double h = (R()- L())/W;
		MoveTo(L(), f(L()));
		//double R = R();
		for (double current = L(); current < R(); current += h)
			LineTo(dc, current, f(current));

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
	void MyPlot(HDC dc, Func fX, Func fY, double tMin=0, double tMax=8* M_PI, bool axes = true) { // эллиптическая ск, параметрическое задание 
		if (axes)
			Axes(dc);
		double t = tMin;
		//double h = (tMax - tMin) / W;
		double h = 1 / (10.*px*sqrt(R()-L()));
		MoveTo(
			cosh(fX(tMin)) * cos(fY(tMin)),
			sinh(fX(tMin)) * sin(fY(tMin)));
		do {

			LineTo(
				dc,
				cosh(fX(t)) * cos(fY(t)),
				sinh(fX(t)) * sin(fY(t))
			);
			t += h;

		} while (t < tMax);
		LineTo(
			dc,
			cosh(fX(tMax)) * cos(fY(tMax)), 
			sinh(fX(tMax)) * sin(fY(tMax))
		);

			
	}
};

#endif SCENE_2D_H