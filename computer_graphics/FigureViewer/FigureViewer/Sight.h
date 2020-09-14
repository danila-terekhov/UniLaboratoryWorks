#ifndef SIGHT_H
#define SIGHT_H

#include "Figure.h"

class Sight : public Figure
{
public:
	Sight(int size=12, int offsetX=50, int offsetY=50) : Figure(size, offsetX, offsetY)
	{
	}
	void Draw(HDC dc)
	{
		HPEN pen = (HPEN) SelectObject( dc, CreatePen(PS_SOLID,3,color) );

		Ellipse( dc, offsetX-size, offsetY-size, offsetX+size, offsetY+size);
		MoveToEx(dc, offsetX-size, offsetY,      NULL);
		LineTo(  dc, offsetX+size, offsetY);
		MoveToEx(dc, offsetX,      offsetY-size, NULL);
		LineTo(  dc, offsetX,      offsetY+size);

		DeleteObject(SelectObject(dc, pen));
	}
	bool InnerPoint(int X, int Y)
	{
		return (X-offsetX)*(X-offsetX)+(Y-offsetY)*(Y-offsetY)<=size*size;
	}
};

#endif SIGHT_H

class Bricket : public Figure
{
public:
	Bricket(int size = 12, int offsetX = 20, int offsetY = 20) : Figure(size, offsetX, offsetY)
	{}
	void Draw(HDC dc)
	{
		HPEN pen = (HPEN) SelectObject( dc, CreatePen(PS_SOLID,3,color) );

		MoveToEx(dc, offsetX - size, offsetY - size, NULL);
		LineTo(dc, offsetX + size, offsetY - size);
		LineTo(dc, offsetX + size, offsetY + size);
		LineTo(dc, offsetX - size, offsetY + size);
		LineTo(dc, offsetX - size, offsetY - size);
		LineTo(dc, offsetX + size, offsetY + size);
		MoveToEx(dc, offsetX + size, offsetY - size, nullptr);
		LineTo(dc, offsetX - size, offsetY + size);

		DeleteObject(SelectObject(dc, pen)); 
	}
	bool InnerPoint(int X, int Y)
	{
		return (X > offsetX - size && X < offsetX +size) && (Y > offsetY-size && Y < offsetY + size);
	}

};

class Spark : public Figure
{
public:
	Spark(int size = 12, int offsetX = 20, int offsetY = 20) : Figure(size, offsetX, offsetY)
	{}
	void Draw(HDC dc)
	{
		HPEN pen = (HPEN) SelectObject( dc, CreatePen(PS_SOLID,3,color) );

		MoveToEx(dc, offsetX - size, offsetY, NULL);
		Arc(dc, -offsetX, -offsetY, offsetX, offsetY, offsetX - size, offsetY, offsetX, offsetY - size);
		DeleteObject(SelectObject(dc, pen)); 
	}
	bool InnerPoint(int X, int Y)
	{
		return (X > offsetX - size && X < offsetX +size) && (Y > offsetY-size && Y < offsetY + size);
	}

};
