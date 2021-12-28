
#include "Matrix3x3.h"


Matrix3x3::Matrix3x3() : Matrix(3, 3) {}

Matrix3x3::Matrix3x3(Vec3 columnVec1, Vec3 columnVec2, Vec3 columnVec3) : Matrix(3, 3)
{
	setColumnVectors(columnVec1, columnVec2, columnVec3);
}

void Matrix3x3::setColumnVectors(Vec3 columnVec1, Vec3 columnVec2, Vec3 columnVec3)
{
	(*this)[1][1] = columnVec1.x;
	(*this)[1][2] = columnVec2.x;
	(*this)[1][3] = columnVec3.x;

	(*this)[2][1] = columnVec1.y;
	(*this)[2][2] = columnVec2.y;
	(*this)[2][3] = columnVec3.y;

	(*this)[3][1] = columnVec1.z;
	(*this)[3][2] = columnVec2.z;
	(*this)[3][3] = columnVec3.z;
}

double Matrix3x3::determinant()
{
	return
		  (*this)[1][1]		* ((*this)[2][2] * (*this)[3][3] - (*this)[2][3] * (*this)[3][2])
		- (*this)[1][2]		* ((*this)[2][1] * (*this)[3][3] - (*this)[2][3] * (*this)[3][1])
		+ (*this)[1][3]		* ((*this)[2][1] * (*this)[3][2] - (*this)[2][2] * (*this)[3][1]);
}

Matrix3x3 Matrix3x3::inverse()
{
	if (determinant() == 0)
	{
		std::cout << "Matrix inverse error: Determinant is 0";
		exit(1);
	}

	Matrix3x3 inv;
	double det = determinant();

	inv[1][1] = ((*this)[2][2] * (*this)[3][3] - (*this)[2][3] * (*this)[3][2]) / det;
	inv[1][2] = ((*this)[1][3] * (*this)[3][2] - (*this)[1][2] * (*this)[3][3]) / det;
	inv[1][3] = ((*this)[1][2] * (*this)[2][3] - (*this)[1][3] * (*this)[2][2]) / det;
	inv[2][1] = ((*this)[2][3] * (*this)[3][1] - (*this)[2][1] * (*this)[3][3]) / det;
	inv[2][2] = ((*this)[1][1] * (*this)[3][3] - (*this)[1][3] * (*this)[3][1]) / det;
	inv[2][3] = ((*this)[1][3] * (*this)[2][1] - (*this)[1][1] * (*this)[2][3]) / det;
	inv[3][1] = ((*this)[2][1] * (*this)[3][2] - (*this)[2][2] * (*this)[3][1]) / det;
	inv[3][2] = ((*this)[1][2] * (*this)[3][1] - (*this)[1][1] * (*this)[3][2]) / det;
	inv[3][3] = ((*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1]) / det;

	return inv;
}
