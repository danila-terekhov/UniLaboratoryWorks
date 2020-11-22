#include "Matrix.h"
#include "AffineTransform.h"
#include "Model2D.h"

using namespace std;

void main()
{
/*
	Matrix<int> M(2);
	cout << "Input M ->\n ";
	cin >> M;

	double a[4] = {1, -2, 3, 0};
	Matrix<> A(2,2, a);
	
	double b[4] = {2, 2, 0, 1};
	Matrix<> B(2,2, b);
	*/
	double a[6] = { 1,2,3,4,5,6 };
	Matrix<> A(3, 2, a);
	Matrix<> B(2, 3, a);

	Matrix<> C = A*B;
	cout
		<< endl << "A =" << endl << A
		<< endl << "B =" << endl << B
		<< endl << "C =" << endl << C
		//<< endl << "A+B =" << endl << (A+B)
		//<< endl << "A-B =" << endl << (A-B)
		<< endl << "T(1,2) =" << endl << Translation(1, 2);

	
	
	Model2D model("vertices.txt", "edges.txt");
	
	cout
		<< endl << "Edges:" << endl << model.GetEdges()
		<< endl << "Vertices before AT:" << endl << model.GetVertices();
	model.Apply(Translation(1, 2));
	cout
		<< endl << "Vertices after AT:" << endl << model.GetVertices();
	cout << endl << model.GetEdges();
		
		
	system("pause");
}
