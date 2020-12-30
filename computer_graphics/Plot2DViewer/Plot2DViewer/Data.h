#define _USE_MATH_DEFINES
#include <cmath>

constexpr auto A = 2;
constexpr auto B = 3;

double					// Исходные значения параметров X0, Y0, px, py
X0 = 200,
Y0 = 200,
px = 10,
py = 100;

double Parabola(double x)
{
	return x * x - 2;
}

double Sinusoid(double x)
{
	return sin(x);	
}

double paramEllX(double t) {
	return t/4 ;
}
double paramEllY(double t) {
	return t;
}