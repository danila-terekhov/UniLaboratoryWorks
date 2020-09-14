#include <windows.h>
#include <windowsx.h>
#include "Sight.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основная процедура
{
	// Первая составляющая часть основной процедуры - создание окна: сначала описывается оконный класс wc, затем создается окно hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// имя оконной процедуры, закрепленной за данным классом
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
		(LPCSTR)"Figure Viewer",					// заголовок окна
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

// В основном модуле объявляется только одна глобальная переменная - создаётся объект класса Sight
// Все дальнейшие действия осуществляются посредством обращения к методам, реализованным в этом классе
Bricket sight(10);

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
{
	sight.SetColor(255, 0, 0);
	HDC dc = GetDC(hWnd);
	RECT r;
	GetClientRect(WindowFromDC(dc), &r);
	switch (msg)
	{
	case WM_PAINT:						// системное сообщение WM_PAINT генерируется всякий раз, когда требуется отрисовка или перерисовка изображения
	{
		SetBkColor(dc, RGB(255,0,0));


		sight.Clear(dc);
		sight.Draw(dc);
		ReleaseDC(hWnd, dc);		// функция ReleaseDC сообщает системе, что связанный с окном hWnd контекст dc больше не нужен
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
		{
			sight.Move(-2, 0, r.right, r.bottom);
			break;
		}
		case VK_RIGHT:
		{
			sight.Move(2, 0, r.right, r.bottom);
			break;
		}
		case VK_DOWN:
		{
			sight.Move(0, -2, r.right, r.bottom);
			break;
		}
		case VK_UP:
		{
			sight.Move(0, 2, r.right, r.bottom);
			break;
		}
		default:
			break;
		}
		InvalidateRect(hWnd, nullptr, false);
		break;
		
	}
	case WM_MOUSEWHEEL:
	{
		POINT P;
		P.x = GET_X_LPARAM(lParam);
		P.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &P);

		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		int c_key = GET_KEYSTATE_WPARAM(wParam) & MK_CONTROL ; 
		sight.Resize(P, delta, c_key, r.right, r.bottom);

		InvalidateRect(hWnd, nullptr, false);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		sight.MoveTo(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), r.right, r.bottom);
		InvalidateRect(hWnd, nullptr, false);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		sight.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (sight.IsDragging())
		{
			sight.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), r.right, r.bottom);
			InvalidateRect(hWnd, nullptr, false);
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		sight.StopDragging();
		break;
	}
	case WM_SIZE:
	{
		InvalidateRect(hWnd, nullptr, false);	// функция InvalidateRect объявляет рабочую область окна hWnd требующей перерисовки, в результате чего генерируется системное сообщение WM_PAINT
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		ReleaseDC(hWnd, dc);
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	ReleaseDC(hWnd, dc);
	return 0;
}