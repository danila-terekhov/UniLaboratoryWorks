#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include <cmath>

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
	}
	void Plot(HDC dc, Func f, bool axes = true)
	{
		if (axes)
			Axes(dc);

		double h = (R()- L())/W;
		MoveTo(L(), Y0);
		for (double current = L(); current < R(); current += h)
			LineTo(dc, current, f(current));

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
	void MyPlot(HDC dc, Func fX, Func fY, bool axes = true) { // эллиптическая ск, параметрическое задание 
		if (axes)
			Axes(dc);

		double h = (2 * M_PI) / W, t = 0;
		do {

			LineTo(
				dc,
				cosh(fX(t)) * cos(fY(t)),
				sinh(fX(t)) * sin(fY(t))
			);
			t += h;

		} while (t <= 2 * M_PI);

			
	}
};

#endif SCENE_2D_H