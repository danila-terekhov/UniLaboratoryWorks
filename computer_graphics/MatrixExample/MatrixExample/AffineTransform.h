#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H


#define OX 1
#define OY 2
#define OO 3

Matrix<> Translation(double x, double y)
{
	double T[] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, T);
}
// Identity() - тождественное АП;
Matrix<> Identity()
{
	double T[] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, T);
}
// Rotation(t) - поворот на угол t;
Matrix<> Rotation(double t)
{
	double T[] = {
		cos(t),-sin(t), 0,
		sin(t),	cos(t), 0,
		0,      0,      1 };
	return Matrix<>(3, T);
}
// Rotation(c, s) - поворот на угол, косинус и синус которого пропорциональны величинам c и s;
Matrix<> Rotation(double c, double s)
{
	double d = 1.0 / sqrt(c*c + s*s);
	double T[] = {
		c*d,-s*d, 0,
		s*d, c*d, 0,
		0,   0,   1 };
	return Matrix<>(3, T);
}
// Scaling(kx, ky) - масштабирование;
Matrix<> Scaling(double kx, double ky)
{
	double T[] = {
		kx, 0,  0,
		0,  ky, 0,
		0,  0,  1 };
	return Matrix<>(3, T);
}
// Mapping (различные виды отражений) - по желанию, для создания матриц отражения можно использовать функцию Scaling.
Matrix<> Mapping(int flag) {
	switch (flag) {
	case OX: return Scaling(-1, 1);
	case OY: return Scaling( 1, -1);
	case OO: return Scaling(-1, -1);
	}
	//unreacheable
	return Matrix<>();
}

#endif AFFINE_TRANSFORM_H