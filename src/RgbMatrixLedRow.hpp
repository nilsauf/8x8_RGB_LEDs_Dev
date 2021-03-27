#ifndef RGB_MATRIX_LED_ROW
#define RGB_MATRIX_LED_ROW

#include <Arduino.h>
#include <MatrixLedList.hpp>
#include <RgbMatrixLed.hpp>

class RgbMatrixLedRow
{
public:
	RgbMatrixLedRow(const uint8_t rowIndex)
	{
		this->RowIndex = rowIndex;
		this->_redLedLists = new MatrixLedList(0 + rowIndex * this->_listCount);
		this->_greenLedLists = new MatrixLedList(1 + rowIndex * this->_listCount);
		this->_blueLedLists = new MatrixLedList(2 + rowIndex * this->_listCount);
	}

	RgbMatrixLedRow *WithRgbLedAt(RgbMatrixLed *led, uint8_t index)
	{
		this->_redLedLists->WithLedAt(led->GetColorLed(Red), index);
		this->_greenLedLists->WithLedAt(led->GetColorLed(Green), index);
		this->_blueLedLists->WithLedAt(led->GetColorLed(Blue), index);

		return this;
	}

	uint8_t GetMaxLedState(ERgbLedColor color)
	{

		switch (color)
		{
		case Red:
			return this->_redLedLists->GetMaxLedState();
		case Green:
			return this->_greenLedLists->GetMaxLedState();
		case Blue:
			return this->_blueLedLists->GetMaxLedState();
		}
	}

	uint8_t RowIndex;

private:
	const uint8_t _listCount = 3;
	MatrixLedList *_redLedLists;
	MatrixLedList *_greenLedLists;
	MatrixLedList *_blueLedLists;
};

#endif