#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Scene2D.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основная процедура
{
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// идентификатор приложения, содержащий адрес начала выделенной ему области памяти
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// имя оконного класса, используемое при создании экземпляров окна
	RegisterClass(&wc);								// регистрация класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функция создания окна заполняет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// имя оконного класса
		(LPCSTR)"Plot2D Viewer",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200, 200, 400, 400,							// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Вторая составляющая часть основной процедуры - основной цикл обработки системных сообщений, который ожидает сообщения и рассылает их соответствующим окнам
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))				// функция GetMessage выбирает из очереди сообщение и заносит его в структуру msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// функция DispatchMessage оповещает систему о необходимости вызова оконной процедуры
	}

	return 0;
}

// В основном модуле объявляется только одна глобальная переменная - создаётся объект класса Scene2D
// Все дальнейшие действия осуществляются посредством обращения к методам, реализованным в этом классе
Scene2D scene(X0, Y0, px, py);

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
{
	switch (msg)
	{
	case WM_CREATE:
	{
		scene.setModel("Vertices.txt", "Edges.txt");
	}
	case WM_PAINT:
	{
		HDC dc = GetDC(hWnd);
		scene.Clear(dc);				// Вызов реализованного в классе Camera2D метода, отвечающего за очистку рабочей области окна hWnd
		//scene.Plot(dc, Sinusoid);
		//scene.MyPlot(dc, paramEllX, paramEllY);
		scene.Render(dc);
		// Вызов реализованного в классе Scene2D метода, отвечающего за отрисовку графика синусоиды
		ReleaseDC(hWnd, dc);
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	case WM_SIZE:
	{
		HDC dc = GetDC(hWnd);
		scene.SetResolution(dc);
		ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	case WM_KEYDOWN:
	{

		switch (wParam)
		{

		case VK_NUMPAD3:
			scene.apply(Translation(0.5, 0));
			break;
		case VK_NUMPAD1:
			scene.apply(Translation(-0.5, 0));
			break;
		case VK_NUMPAD5:
			scene.apply(Translation(0, 0.5));
			break;
		case VK_NUMPAD2:
			scene.apply(Translation(0, -0.5));
			break;


		case VK_NUMPAD4:
			scene.apply(Rotation(3.14 / 36));
			break;
		case VK_NUMPAD6:
			scene.apply(Rotation(-3.14 / 36));
			break;

		case VK_NUMPAD7:
			scene.apply(Mapping(OX));
			break;
		case VK_NUMPAD8:
			scene.apply(Mapping(OY));
			break;
		case VK_NUMPAD9:
			scene.apply(Mapping(OO));
			break;

		case VK_OEM_PLUS:
			scene.apply(Scaling(1.2, 1.2));
			break;

		case VK_OEM_MINUS:
			scene.apply(Scaling(0.8, 0.8));
			break;


		}
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}


	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}
	case WM_LBUTTONUP:
	{
		scene.StopDragging();
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (scene.isDragging){
			scene.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			InvalidateRect(hWnd, nullptr, false);
		}
	return 0;
	}
	case WM_MOUSEWHEEL:
	{

		POINT P;
		P.x = GET_X_LPARAM(lParam);
		P.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &P);

		scene.Resize(
			P.x,
			P.y,
			GET_WHEEL_DELTA_WPARAM(wParam) > 0);

		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}