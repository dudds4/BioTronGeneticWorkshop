#include "Matrix.h"

Matrix::Matrix(int rows, int cols) {
	m_rows = rows;
	m_columns = cols;

	int numIndices = m_rows * m_columns;
	data = new float[numIndices];
	for(int i = 0; i < numIndices; i++) {
		data[0] = 0;
	}
}

Matrix::Matrix(const Matrix &source) {
	int sizeOfData = source.numRows() * source.numCols();
	this->data = new float[sizeOfData];
	this->m_rows = source.numRows();
	this->m_columns = source.numCols();

	for(int i = 0; i < sizeOfData; i++)
		this->data[i] = source.data[i];
}

Matrix& Matrix::operator=(const Matrix &source) {
	if(this == &source) return *this;

	int sizeOfData = source.numRows() * source.numCols();
	if(sizeOfData != this->numRows() * this->numCols()) {
		delete[] this->data;
		this->data = new float[sizeOfData];
	}
	this->m_rows = source.numRows();
	this->m_columns = source.numCols();
	for(int i = 0; i < sizeOfData; i++)
		this->data[i] = source.data[i];

	return *this;
}

Matrix::~Matrix() {
	delete[] data;
	data = 0;
}

int Matrix::get(int row, int column) const {
	return data[row * m_columns + column];
}

bool Matrix::set(int row, int column, float value) {
	if(row < 0 || row >= m_rows || column < 0 || column >= m_columns) return false;
	data[row * m_columns + column] = value;
	return true;
}

int Matrix::numRows() const { return m_rows; }
int Matrix::numCols() const { return m_columns; }

Matrix Matrix::add(Matrix other) const {
	Matrix result(this->m_rows, this->m_columns);
	if(this->numRows() != other.numRows() || this->numCols() != other.numCols()) return result;

	int numIndices = m_rows * m_columns;
	for(int i = 0; i < numIndices; i++)
		result.data[i] = this->data[i] + other.data[i];

	return result;
}

Matrix Matrix::scale(float factor) const {
	Matrix result(numRows(), numCols());
	int length = numRows() * numCols();
	for(int i = 0; i < length; i++)
		result.data[i] = this->data[i] * factor;

	return result;
}

Matrix Matrix::leftMultiply(Matrix other) const {
	return other.rMultiply(*this);
}
Matrix Matrix::rightMultiply(Matrix other) const {
	return this->rMultiply(other);
}

Matrix Matrix::rMultiply(Matrix other) const {
	if(this->numCols() != other.numRows()) {
		//failure
		Matrix m(1, 1);
		return m;
	}

	int resultantRows = this->numRows();
	int resultantCols = other.numCols();
	Matrix result(resultantRows, resultantCols);

	int value;
	for(int i = 0; i < resultantRows; i++)
		for(int j = 0; j < resultantCols; j++) {
			//compute row_i dot column_j
			value = 0;
			for(int k = 0; k < this->numCols(); k++)
				value += this->get(i, k) * other.get(k, j);

			result.set(i, j, value);
		}

	return result;
}
