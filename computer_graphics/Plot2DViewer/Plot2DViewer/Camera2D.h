#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>
#include <iostream>
#include <iostream>

class Camera2D
{
public:
	bool isDragging;
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат
	double px, py;						// Единицы масштаба мировой системы координат, выраженные в пикселях
	double prevX0, prevY0;

	int W, H;							// Разрешение рабочей области окна
	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return (int)(X0 + px * X + 0.5);
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return (int)(Y0 - py * Y + 0.5);
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return (X - X0 + 0.5) / px;
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return -(Y - Y0 + 0.5) / py;
	}
	double L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return ScreenToWorldX(0);
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return ScreenToWorldX(W);
	}
	double T()
	{
		return ScreenToWorldY(0);
	}
	double B() 
	{
		return ScreenToWorldY(H);
	}
private:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
	{
	}
	void Clear(HDC dc)
	{
		Rectangle(dc, 0, 0, W-1, H-1);
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);

		if (!W && !H)
		{
			W = r.right+1;
			H = r.bottom+1;
		}

		double W1 = double(r.right+1) / W;
		double H1 = double(r.bottom+1) / H;


		X0 *= W1;
		Y0 = W1 * (px / py) * Y0 + (H / 2) * (H1 - W1 * (px / py));
		py = px * W1;
		px *= W1;
		

		W = r.right+1;
		H = r.bottom+1;
		
		// Данная процедура вызывается при изменении размеров окна
		// В ней задаются значения величин W, H, а также настраиваются значения параметров X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
	}
	void LineTo(HDC dc, double X, double Y)
	{
		MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		WIN32::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
	}
	void Axes(HDC dc)
	{

		WIN32::MoveToEx(dc, 0, Y0, 0);
		WIN32::LineTo(dc, W, Y0);
		WIN32::MoveToEx(dc, X0, 0, 0);
		WIN32::LineTo(dc, X0, H);
	}
	void StartDragging(int X, int Y)
	{
		prevX0 = X;
		prevY0 = Y;
		isDragging = true;
	}

	void StopDragging()
	{
		isDragging = false;
	}

	void Drag(int X, int Y)
	{
		X0 += X - prevX0;
		Y0 += Y - prevY0;
		prevX0 = X;
		prevY0 = Y;
	}
	void Resize(int X, int Y, bool inc)
	{
		double
			k = inc ? 0.1 : -0.1,
			XW = ScreenToWorldX(X),
			YW = ScreenToWorldY(Y);
		X0 -= k * px * XW;
		Y0 += k * py * YW;
		px = (1.0 + k) * px;
		py = (1.0 + k) * py;
	}
};

#endif CAMERA_2D_H