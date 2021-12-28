
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

	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			(*this)[i][j] = (*copiedMatrix.rowVectors[i-1])[j];
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

	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			(*this)[i][j] = (*copiedMatrix.rowVectors[i-1])[j];
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
	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= width; j++)
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
		std::cout << "Matrix multiplication error: Incompatible dimensions";
		exit(1);
	}
		
	Matrix product(height, m0.getWidth());
	int dot_len = width;

	for (int i = 1; i <= product.getHeight(); i++)
	{
		for (int j = 1; j <= product.getWidth(); j++)
		{
			// Calculate element at i, j as a dot product of this matrix's row i and m0's column j
			for (int dot_idx = 1; dot_idx <= dot_len; dot_idx++)
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
	if (heightIndex > height || heightIndex <= 0)
	{
		std::cout << "Matrix element access error: Row index out of range";
		exit(1);
	}


	return *(rowVectors[heightIndex - 1]);
}

Matrix Matrix::multiply(double multiplier)
{
	Matrix product(height, width);

	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			product[i][j] = (*this)[i][j] * multiplier;
		}
	}

	return product;
}

Matrix Matrix::operator * (double multiplier)
{
	return multiply(multiplier);
}


Matrix operator * (double multiplier, Matrix m0)
{
	return m0 * multiplier;
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
	if (widthIndex > width || widthIndex <= 0)
	{
		std::cout << "Matrix element access error: Column index out of range";
		exit(1);
	}

	return elements[widthIndex - 1];
}
