#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H


#define OX 1
#define OY 2
#define OO 3

// Identity() - тождественное АП;
Matrix<> Identity()
{
	double T[] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}
Matrix<> Identity3D()
{
	double T[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	return Matrix<>(4, 4, T);
}



Matrix<> Translation(double x, double y)
{
	double T[] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}
Matrix<> Translation(double x, double y, double z)
{
	double T[] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1};
	return Matrix<>(4, 4, T);
}



// Scaling(kx, ky) - масштабирование;
Matrix<> Scaling(double kx, double ky)
{
	double T[] = {
		kx, 0,  0,
		0,  ky, 0,
		0,  0,  1 };
	return Matrix<>(3, 3, T);
}
// Scaling(kx, ky) - масштабирование;
Matrix<> Scaling(double kx, double ky, double kz)
{
	double T[] = {
		kx, 0,  0,  0,
		0,  ky, 0,  0,
		0,  0,  kz, 0,
		0,  0,  0,  1 };
	return Matrix<>(4, 4, T);
}



// Rotation(t) - поворот на угол t;
Matrix<> Rotation(double t)
{
	double T[] = {
		cos(t),-sin(t), 0,
		sin(t),	cos(t), 0,
		0,      0,      1 };
	return Matrix<>(3, 3, T);
}
Matrix<> RotationX(double t)
{
	double T[] = {
		1.0, 0.0,		0.0,	 0.0,
		0.0, cos(t),	-sin(t), 0.0,
		0.0, sin(t),	cos(t),	 0.0,
		0.0, 0.0,		0.0,	 1.0 };
	return Matrix<>(4, 4, T);
}
Matrix<> RotationY(double t)
{
	double T[] = {
		cos(t), 0.0, sin(t), 0.0,
		0.0,	1.0, 0.0,	 0.0,
		-sin(t),0.0, cos(t), 0.0,
		0.0,	0.0, 0.0,	 1.0 };
	return Matrix<>(4, 4, T);
}
Matrix<> RotationZ(double t) {
	double T[] = {
		cos(t), -sin(t), 0.0, 0.0,
		sin(t), cos(t),  0.0, 0.0,
		0.0,	0.0,	 1.0, 0.0,
		0.0,	0.0,	 0.0, 1.0 };
	return Matrix<>(4, 4, T);
}

// Rotation(c, s) - поворот на угол, косинус и синус которого пропорциональны величинам c и s;
Matrix<> Rotation(double c, double s)
{
	double d = 1.0 / sqrt(c * c + s * s);
	double T[] = {
		c*d, -s*d, 0,
		s*d, c*d,  0,
		0,   0,    1 };
	return Matrix<>(3, 3, T);
}
Matrix<> rotationX(double c, double s)
{
	double d = 1.0 / sqrt(c * c + s * s);
	double T[] = {
		1, 0,	0,	  0,
		0, c*d, -s*d, 0,
		0, s*d, c*d,  0,
		0, 0,	0,	  1 };
	return Matrix<>(4, 4, T);
}
Matrix<> rotationY(double c, double s)
{
	double d = 1.0 / sqrt(c * c + s * s);
	double T[16] = {
		c*d,  0, s*d, 0,
		0,    1, 0,   0,
		-s*d, 0, c*d, 0,
		0,	  0, 0,   1 };
	return Matrix<>(4, 4, T);
}
Matrix<> rotationZ(double c, double s)
{
	double d = 1.0 / sqrt(c * c + s * s);
	double T[16] = {
		c*d, -s*d, 0, 0,
		s*d, c*d,  0, 0,
		0,   0,    1, 0,
		0,   0,    0, 1 };
	return Matrix<>(4, 4, T);
}



// Mapping (различные виды отражений) - по желанию, для создания матриц отражения можно использовать функцию Scaling.
Matrix<> Mapping(int flag) {
	return Scaling(
		flag & OX ? -1 : 1,
		flag & OY ? -1 : 1
	);
}

#endif AFFINE_TRANSFORM_H