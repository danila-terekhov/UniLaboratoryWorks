#include "Matrix.h"
#include "AffineTransform.h"
#include "Model3D.h"

using namespace std;

void main()
{


	Model3D model("Vertices3D.txt", "Faces.txt");
	
	cout
		<< endl << "Faces:" << endl << model.getFaces()
		<< endl << "Edges:" << endl << model.GetEdges()
		<< endl << "Vertices before AT:" << endl << model.GetVertices();
	//model.Apply(Translation(1, 2));
	

		
	system("pause");
}
