class Matrix {
public:
	Matrix(int, int);
	Matrix(const Matrix &source);
	Matrix& operator=(const Matrix &source);
	
	~Matrix();

	int get(int, int) const;
	bool set(int, int, int);

	int numRows() const;
	int numCols() const;

	Matrix add(Matrix) const;
	Matrix scale(float) const;
	Matrix leftMultiply(Matrix) const;
	Matrix rightMultiply(Matrix) const;
	
private:
	Matrix rMultiply(Matrix) const;
	int* data;
	int m_rows;
	int m_columns;
};