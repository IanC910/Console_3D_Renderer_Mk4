
#include "Matrix.h"


/////////////////////////////
// Class Matrix Methods
/////////////////////////////

Matrix::Matrix(int initHeight, int initWidth) : height(initHeight), width(initWidth)
{
	rowVectors = new RowVector*[height];
	for (int i = 0; i < height; i++)
		rowVectors[i] = new RowVector(width);
}

Matrix::Matrix(const Matrix &copiedMatrix) : height(copiedMatrix.height), width(copiedMatrix.width)
{
	rowVectors = new RowVector * [height];
	for (int i = 0; i < height; i++)
		rowVectors[i] = new RowVector(width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			(*this)[i][j] = (*copiedMatrix.rowVectors[i])[j];
		}
	}
}

void Matrix::operator = (const Matrix& copiedMatrix)
{
	for (int i = 0; i < height; i++)
	{
		delete rowVectors[i];
	}
	delete[] rowVectors;

	height = copiedMatrix.getHeight();
	width = copiedMatrix.getWidth();

	rowVectors = new RowVector * [height];
	for (int i = 0; i < height; i++)
		rowVectors[i] = new RowVector(width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			(*this)[i][j] = (*copiedMatrix.rowVectors[i])[j];
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < height; i++)
	{
		delete rowVectors[i];
	}

	delete[] rowVectors;
	rowVectors = nullptr;
}

void Matrix::set0()
{
	for (int i = 0; i < height; i++)
	{
		rowVectors[i]->set0();
	}
}

void Matrix::print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << (*this)[i][j] << "  ";
		}

		std::cout << "\n";
	}
}

int Matrix::getHeight() const
{
	return height;
}

int Matrix::getWidth() const
{
	return width;
}

Matrix Matrix::multiply(Matrix& m0)
{
	if (width != m0.getHeight())
	{
		std::cout << "Matrix multiplication error: Incampatible dimensions";
		exit(1);
	}
		
	Matrix product(height, m0.getWidth());
	int dot_len = width;

	for (int i = 0; i < product.getHeight(); i++)
	{
		for (int j = 0; j < product.getWidth(); j++)
		{
			// Calculate element at i, j as a dot product of this matrix's row i and m0's column j
			for (int dot_idx = 0; dot_idx < width; dot_idx++)
			{
				product[i][j] += (*this)[i][dot_idx] * m0[dot_idx][j];
			}
		}
	}

	return product;
}

Matrix Matrix::operator * (Matrix& m0)
{
	return multiply(m0);
}

Matrix::RowVector& Matrix::operator [] (int heightIndex)
{
	return *(rowVectors[heightIndex]);
}

Matrix Matrix::multiply(double multiplier)
{
	Matrix product(height, width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			product[i][j] = (*this)[i][j] * multiplier;
		}
	}

	return product;
}


/////////////////////////////
// Class RowVector Methods
/////////////////////////////

Matrix::RowVector::RowVector(int initWidth) : width(initWidth)
{
	elements = new double[width];

	set0();
}

Matrix::RowVector::~RowVector()
{
	delete[] elements;

	elements = nullptr;
}

void Matrix::RowVector::set0()
{
	for (int j = 0; j < width; j++)
	{
		elements[j] = 0;
	}
}

double& Matrix::RowVector::operator [] (int widthIndex)
{
	return elements[widthIndex];
}
