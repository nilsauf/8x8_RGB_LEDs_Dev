#ifndef RGB_MATRIX
#define RGB_MATRIX

#include <Arduino.h>
#include <RgbMatrixLedRow.hpp>
#include <MatrixLedList.hpp>

class RgbMatrix
{
public:
	RgbMatrix(const uint8_t rowCount, const uint8_t columnCount)
	{
		this->_rowCount = rowCount;
		this->_columnCount = columnCount;

		this->_rows = (RgbMatrixLedRow **)malloc(rowCount * sizeof(RgbMatrixLedRow *));
		this->_columns = (MatrixLedList **)malloc(columnCount * sizeof(MatrixLedList *));
	}

	RgbMatrix *WithRowAt(RgbMatrixLedRow *row, uint8_t index)
	{
		if (index < 0 || index > this->_rowCount)
		{
			throw "Index need to be greater than " + this->_rowCount;
		}

		this->_rows[index] = row;

		return this;
	}

	RgbMatrix *WithColumnAt(MatrixLedList *row, uint8_t index)
	{
		if (index < 0 || index > this->_rowCount)
		{
			throw "Index need to be greater than " + this->_rowCount;
		}

		this->_columns[index] = row;

		return this;
	}

private:
	uint8_t _rowCount;
	uint8_t _columnCount;

	RgbMatrixLedRow **_rows;
	MatrixLedList **_columns;
};

#endif