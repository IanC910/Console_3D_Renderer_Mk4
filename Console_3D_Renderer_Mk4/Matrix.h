#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
	class RowVector;

public:

	// Constructor with height and width as arguments
	Matrix(int, int);

	// Coyp constructor
	Matrix(const Matrix&);
	
	// Deep copy
	void operator = (const Matrix&);
	
	~Matrix();

	void set0();

	void print();

	int getHeight() const;
	int getWidth() const;

	// Matrix multiplication
	// Works only if *this has the same number of columns as the argument has rows
	Matrix multiply(Matrix&);

	Matrix operator * (Matrix&);

	RowVector& operator [] (int);

	// Scalar multiplication
	// Multiplies every element in the matrix by the argument
	Matrix multiply(double);

private:
	
	int height;
	int width;
	RowVector** rowVectors;
};


class Matrix::RowVector
{
public:

	// Constructor with height as its arguments
	RowVector(int);

	~RowVector();

	void set0();

	double& operator [] (int);

private:

	const int width;
	double* elements;
};

#endif

