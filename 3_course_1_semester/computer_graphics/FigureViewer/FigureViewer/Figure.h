#ifndef FIGURE_H
#define FIGURE_H

class Figure
{
protected:
	int size;
	int offsetX, offsetY;
	COLORREF color;
private:
	bool isDragging;
	int previousX, previousY;
public:
	Figure(int size, int offsetX, int offsetY) : size(size), offsetX(offsetX), offsetY(offsetY), isDragging(false), previousX(0), previousY(0), color(RGB(0,0,0))
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
	//	Rectangle(dc, 0, 0, r.right, r.bottom);
        HRGN bgRgn = CreateRectRgnIndirect(&r);
        HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));
        FillRgn(dc, bgRgn, hBrush);
	}
	virtual void Draw(HDC dc) = 0;
	virtual bool InnerPoint(int X, int Y) = 0;
	void MoveTo(int X, int Y, int sizeX, int sizeY)
	{
		
		if (X < size)
			offsetX = size;
		else if (X > (sizeX - size))
			offsetX = sizeX - size;
		else offsetX = X;

		if (Y < size)
			offsetY = size;
		else if (Y > (sizeY - size))
			offsetY = sizeY - size;
		else offsetY = Y;
	}
	void Resize(POINT P, int delta, int c_key, int sizeX, int sizeY) {
		if (c_key && InnerPoint(P.x, P.y)) {
			size += delta / 25;
			if (size > sizeX / 2)
				size = sizeX/2;
			if (size > sizeY / 2)
				size = sizeY/2;
			MoveTo(offsetX, offsetY, sizeX, sizeY);
		}

	}
	void SetColor(int R=0, int G=0, int B=0)
	{
		color = RGB(R, G, B);
	}
	void Move(int X, int Y, int sizeX, int sizeY)
	{
		int newX = offsetX + X;
		int newY = offsetY - Y;
		MoveTo(newX, newY, sizeX, sizeY);
		/*
		if (newX < size)
			offsetX = size;
		else if (newX > (sizeX - size))
			offsetX = sizeX - size;
		else offsetX = newX;

		if (newY < size)
			offsetY = size;
		else if (newY > (sizeY - size))
			offsetY = sizeY - size;
		else offsetY = newY;
		*/
	}
	void StartDragging(int X, int Y)
	{
		isDragging = InnerPoint(X, Y);
		if (isDragging) {
			previousX = X;
			previousY = Y;
		}
	}
	void Drag(int X, int Y, int sizeX, int sizeY)
	{
		int diffX =	previousX - offsetX;
		int diffY = previousY - offsetY;
	
		MoveTo(X - diffX, Y - diffY, sizeX, sizeY);
		previousX = X;
		previousY = Y;
		/*
		if (X < size)
			offsetX = size;
		else if (X > (sizeX - size))
			offsetX = sizeX - size;
		else offsetX = X;

		if (Y < size)
			offsetY = size;
		else if (Y > (sizeY - size))
			offsetY = sizeY - size;
		else offsetY = Y;
		*/

	}
	void StopDragging()
	{
		isDragging = false;
	}
	bool IsDragging()
	{
		return isDragging;
	}
};

#endif FIGURE_H
