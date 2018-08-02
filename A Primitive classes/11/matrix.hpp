// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

/*****************************************************************************/

#include <iostream>
#include <stdexcept> 

/*****************************************************************************/


class Matrix
{

	/*-----------------------------------------------------------------*/

public:

	/*------------------------------------------------------------------*/

	template< typename _MatrixType >
	class MatrixRowAccessor
	{
		_MatrixType & m_matrix;
		const int m_rowIndex;

	public:

		MatrixRowAccessor(_MatrixType & _matrix, int _rowIndex)
			: m_matrix(_matrix)
			, m_rowIndex(_rowIndex)
		{}

		double operator[] (int _columnIndex) const
		{
			if (_columnIndex >= m_matrix.m_col || _columnIndex < 0 || m_rowIndex >= m_matrix.m_row || m_rowIndex < 0)
				throw std::logic_error("Out of range");

			return m_matrix.m_pData[m_rowIndex][_columnIndex];
		}

		double& operator[] (int _columnIndex)
		{
			if (_columnIndex >= m_matrix.m_col || _columnIndex < 0 || m_rowIndex >= m_matrix.m_row || m_rowIndex < 0)
				throw std::logic_error("Out of range");

			return m_matrix.m_pData[m_rowIndex][_columnIndex];
		}
	};


	/*****************************************************************************/

	template< typename > friend class MatrixRowAccessor;

	/*------------------------------------------------------------------*/


	MatrixRowAccessor< const Matrix > operator[] (int _rowIndex) const;

	MatrixRowAccessor< Matrix > operator[] (int _rowIndex);

	Matrix(
		const int _i,
		const int _j
	);

	Matrix(
		const int _i,
		const int _j,
		double * _pData
	);

	Matrix(const Matrix & _matrix);

	Matrix & operator = (const Matrix & _matrix);

	Matrix(Matrix && _matrix);

	Matrix & operator = (Matrix && _matrix);

	~Matrix();

	bool operator == (const Matrix & _matrix) const;

	bool operator != (const Matrix & _matrix) const;

	void operator += (const Matrix & _matrix);

	void operator *= (const Matrix & _matrix);

	void operator -= (const Matrix & _matrix);

	void operator *= (const double _scale);

	Matrix operator + (const Matrix & _matrix) const;

	Matrix operator * (const Matrix & _matrix) const;

	Matrix operator - (const Matrix & _matrix) const;

	Matrix operator * (const double _scale) const;

	friend std::ostream & operator << (std::ostream & _s, const Matrix & _m);

	int getNumRows() const;

	int getNumColumns() const;

	/*------------------------------------------------------------------*/

private:

	int m_row, m_col;

	double ** m_pData;

};

/*****************************************************************************/

inline
int Matrix::getNumRows() const
{
	return m_row;
}

/*****************************************************************************/

inline
int Matrix::getNumColumns() const
{
	return m_col;
}


/*****************************************************************************/

#endif //  _MATRIX_HPP_