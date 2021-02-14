#include "stdio.h"

double f(double x) {
	return 2*x*x - 12*x
}
int main(){
	double a,b,e,k;
	// step 1
	a = 0;
	b = 10;
	e = 1;
	k = 0;
	double x, y, z, f_x, f_y, f_z, abs_l;
	// step 2
	x = (a+b)/2 ;
	abs_l = b-a;
	f_x = f(x);

	while (1) {
		// step 3
		y = a + abs_l/4;
		z = b - abs_l/4;
		f_y = f(y);
		f_z = f(z);
		// step 4
		if (f_y < f_x) {
			b = x;
			//a = a;
			x = y;
			goto step6;
		} else {
			goto step5;
		}
		step5:
		if (f_z < f_x) {
			a = x;
			//b = b;
			x = z;
			//goto step6;
		} else {
			a = y;
			b = z;
			//x = x;
		}
		step6:


	}




}
