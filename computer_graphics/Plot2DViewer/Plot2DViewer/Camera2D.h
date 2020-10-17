#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>
#include <iostream>
#include <iostream>

class Camera2D
{
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат
	double px, py;						// Единицы масштаба мировой системы координат, выраженные в пикселях
	int W, H;							// Разрешение рабочей области окна
	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return X0 + px * X + 0.5;
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return Y0 - py * Y + 0.5;
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
		return -X0/px;
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (W-X0)/px;
	}
private:
	double posX=0, posY=0;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py, int W, int H) : X0(X0), Y0(Y0), px(px), py(py), W(W), H(H)
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
		int WN = r.right + 1;
		int HN = r.bottom + 1;

		X0 = (WN / W) * X0;
		Y0 = (WN / W) * (px / py) * Y0 + (H / 2) * ((HN / H) - ((WN / W) * (px / py)));
		px = (WN / W) * px;
		py = (WN / W) * py;

		W = WN;
		H = HN;

		// Данная процедура вызывается при изменении размеров окна
		// В ней задаются значения величин W, H, а также настраиваются значения параметров X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
	}
	void MoveTo(HDC dc, double X, double Y)
	{
		posX = ScreenToWorldX(X);
		posY  = ScreenToWorldY(Y);
		::MoveToEx(dc, posX, posY, 0);
	}
	void LineTo(HDC dc, double X, double Y)
	{
		posX = ScreenToWorldX(X);
		posY = ScreenToWorldY(Y);
		::LineTo(dc, posX, posY);
	}
	void Axes(HDC dc)
	{
		MoveTo(dc, 0, 0);
		LineTo(dc, 10,10);

	}
};

#endif CAMERA_2D_H