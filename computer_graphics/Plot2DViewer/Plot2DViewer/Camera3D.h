#pragma once

#include "Camera2D.h"
#include "Matrix.h"
#include "Vector3D.h"

class Camera3D : public Camera2D {
protected:
	Vector3D<> Ov, T, N;
	double D; // unsigned double doesn't exist 

	Matrix<> WorldToView,		// 4x4 
			 ViewToProject,     // 3x4
			 WorldToProject;    // 3x4
	/*
	void setOv(double* Ov) {
		this->Ov = Ov;
	}
	void setT(double* T) {
		this->T = T;
	}
	void setN(double* N) {
		this->N = N;
	}
	*/
	void setOv(const Vector3D<>& Ov) {
		this->Ov = Ov;
	}
	void setT(const Vector3D<>& T) {
		this->T = T;
	}
	void setN(const Vector3D<>& N) {
		this->N = N;
	}

public:
	Camera3D(double X0, double Y0, double px, double py) :
		Camera2D(X0, Y0, px, py), Ov(), T(), N()
	{
		D = 16;
		T(0, 1, 0);
		Ov(10, 10, 10);
		N(0, 0, 1);
		updateCamera();
	}


	void updateCamera() // обновление матриц перехода.
	{
		Vector3D<> k = N * (1.0 / N.Norm());
		Vector3D<> i = (T.VectorProd(N)) * (1.0 / (T.VectorProd(N)).Norm());
		Vector3D<> j = (k.VectorProd(i)) * (1.0 / (k.VectorProd(i)).Norm());

		// S v->p
		double T1[] = {
			1, 0, 0, 0,
			0, 1, 0 ,0,
			0, 0, -1/D, 1
		};
		ViewToProject = Matrix<>(3, 4, T1);

		//  S w->v
		double T2[] = {
			i(1), i(2), i(3), -(Ov.ScalarProd(i)),
			j(1), j(2), j(3), -(Ov.ScalarProd(j)),
			k(1), k(2), k(3), -(Ov.ScalarProd(k)),
			0, 0, 0, 1
		};
		WorldToView = Matrix<>(4, 4, T2);

		//  S w->p
		WorldToProject = ViewToProject * WorldToView;
	}



};

