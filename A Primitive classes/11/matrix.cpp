// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "matrix.hpp"


/*****************************************************************************/

std::ostream & operator<<(std::ostream & _s, const Matrix & _m)
{
	for (int i = 0; i < _m.m_row; i++)
	{
		for (int j = 0; j < _m.m_col; j++)
		{
			_s << _m.m_pData[i][j];
			if (j < _m.m_col - 1)
				_s << '\t';
		}
		_s << '\n';
	}
	return _s;
}

/*****************************************************************************/

bool Matrix::operator==(const Matrix & _matrix) const
{
	if (m_row != _matrix.m_row || m_col != _matrix.m_col)
		return false;

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			if (m_pData[i][j] != _matrix.m_pData[i][j]) 
				return false;

	return true;
}

/*****************************************************************************/

bool Matrix::operator!=(const Matrix & _matrix) const
{
	return !(*this==_matrix);
}

/*****************************************************************************/

void Matrix::operator+=(const Matrix & _matrix)
{
	if (m_row != _matrix.m_row || m_col != _matrix.m_col)
		throw std::logic_error("Size mismatch");

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			m_pData[i][j] += _matrix.m_pData[i][j];
}

/*****************************************************************************/

void Matrix::operator*=(const Matrix & _matrix)
{
	if (m_col != _matrix.m_row)
		throw std::logic_error("Size mismatch");

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			m_pData[i][j] *= _matrix.m_pData[j][i];
}

/*****************************************************************************/

void Matrix::operator-=(const Matrix & _matrix)
{
	if (m_row != _matrix.m_row || m_col != _matrix.m_col)
		throw std::logic_error("Size mismatch");

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			m_pData[i][j] -= _matrix.m_pData[i][j];
}

/*****************************************************************************/

void Matrix::operator*=(const double _scale)
{
	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			m_pData[i][j] *= _scale;
}

/*****************************************************************************/

Matrix Matrix::operator+(const Matrix & _matrix) const
{
	if (m_row != _matrix.m_row || m_col != _matrix.m_col)
		throw std::logic_error("Size mismatch");

	Matrix temp(m_row, m_col);

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			temp.m_pData[i][j] = m_pData[i][j] + _matrix.m_pData[i][j];

	return temp;
}

/*****************************************************************************/

Matrix Matrix::operator*(const Matrix & _matrix) const
{
	if (m_col != _matrix.m_row)
		throw std::logic_error("Size mismatch");

	Matrix temp(m_row, _matrix.m_col);

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < _matrix.m_col; j++)
			for (int k = 0; k < m_col; k++)
				temp.m_pData[i][j] += m_pData[i][k] * _matrix.m_pData[k][j];
			
	return temp;
}

/*****************************************************************************/

Matrix Matrix::operator-(const Matrix & _matrix) const
{
	if (m_row != _matrix.m_row || m_col != _matrix.m_col)
		throw std::logic_error("Size mismatch");

	Matrix temp(m_row, m_col);

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			temp.m_pData[i][j] = m_pData[i][j] - _matrix.m_pData[i][j];

	return temp;
}

/*****************************************************************************/

Matrix Matrix::operator*(const double _scale) const
{
	Matrix temp(m_row, m_col);

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			temp.m_pData[i][j] = m_pData[i][j] * _scale;

	return temp;
}

/*****************************************************************************/

Matrix::MatrixRowAccessor<const Matrix> Matrix::operator[](int _rowIndex) const
{
	return MatrixRowAccessor<const Matrix>(*this,_rowIndex);
}

/*****************************************************************************/

Matrix::MatrixRowAccessor<Matrix> Matrix::operator[](int _rowIndex)
{
	return MatrixRowAccessor<Matrix>(*this,_rowIndex);
}

/*****************************************************************************/

Matrix::Matrix(
	const int _i,
	const int _j
)
	: m_row(_i)
	, m_col(_j)
{
	if (_i < 1 || _j < 1)
		throw std::logic_error("Invalid dimensions");

	m_pData = new double *[m_row];
	for (int i = 0; i < m_row; i++)
		m_pData[i] = new double[m_col];

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			m_pData[i][j] = 0;
}

/*****************************************************************************/

Matrix::Matrix(
	const int _i,
	const int _j,
	double * _pData
)
	: Matrix(_i, _j)
{
	if (_pData == nullptr)
		throw std::logic_error("Bad data pointer");

	m_pData = new double *[m_row];
	for (int i = 0; i < m_row; i++)
		m_pData[i] = new double[m_col];

	for (int i = 0; i < m_row; i++)
		for (int j = 0, inc = 0; j < m_col; j++, inc++)
			m_pData[i][j] = *_pData++;

}

/*****************************************************************************/

Matrix::Matrix(const Matrix & _matrix)
{
	m_col = _matrix.m_col;
	m_row = _matrix.m_row;

	m_pData = new double *[m_row];
	for (int i = 0; i < m_row; i++)
		m_pData[i] = new double[m_col];

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			m_pData[i][j] = _matrix.m_pData[i][j];
}

/*****************************************************************************/

Matrix & Matrix::operator=(const Matrix & _matrix)
{

	m_col = _matrix.m_col;
	m_row = _matrix.m_row;

	m_pData = new double *[m_row];
	for (int i = 0; i < m_row; i++)
		m_pData[i] = new double[m_col];

	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			m_pData[i][j] = _matrix.m_pData[i][j];
	 
	return *this;
}

/*****************************************************************************/

Matrix::Matrix(Matrix && _matrix)
{
	std::swap(m_col,_matrix.m_col);
	std::swap(m_row,_matrix.m_row);
	std::swap(m_pData, _matrix.m_pData);
}

/*****************************************************************************/

Matrix & Matrix::operator=(Matrix && _matrix)
{
	std::swap(m_col , _matrix.m_col);
	std::swap(m_row,_matrix.m_row);
	std::swap(m_pData, _matrix.m_pData);

	return * this;
}

/*****************************************************************************/

Matrix::~Matrix()
{
	for (int i = 0; i < m_row; i++)
		delete[] m_pData[i];
	delete[] m_pData;
}

/*****************************************************************************/