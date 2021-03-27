#ifndef Matrix_SHIFT_REGISTER
#define Matrix_SHIFT_REGISTER

#if !defined(ESP8266)
#error This code is designed to run on ESP8266 and ESP8266-based boards! Please check your Tools->Board setting.
#endif

#include <Arduino.h>
#include <ESP8266TimerInterrupt.h>
#include <FastEsp8266ShiftRegister.hpp>

class MatrixShiftRegister
{
public:
    MatrixShiftRegister(const uint8_t dataPin, const uint8_t clockPin, const uint8_t latchPin)
        : MatrixShiftRegister(new FastEsp8266ShiftRegister(dataPin, clockPin, latchPin, 4))
    {
    }

    MatrixShiftRegister(FastEsp8266ShiftRegister *shiftRegister)
    {
        this->_shiftRegister = shiftRegister;

        this->_data = (uint8_t *)malloc(this->DataArrayLength * sizeof(uint8_t));
        for (int dataIndex = 0; dataIndex < this->DataArrayLength; dataIndex++)
        {
            this->_data[dataIndex] = 0;
        }

        MatrixShiftRegister::Singleton = this; // make this object accessible for timer interrupts

        this->Timer = ESP8266Timer();
    }

    /**
     * @brief Swaps the current data array to another array of the same size
     * 
     * @param newDataArray The pointer to a new data array, size needs to be the same size of the current data array
     * @return uint8_t* The pointer to the current data array (can be swaped back)
     */
    uint8_t *SwapDataArray(uint8_t *newDataArray)
    {
        noInterrupts();
        uint8_t *oldDataArray = this->_data;
        this->_data = newDataArray;
        this->_time = 0;
        interrupts();
        return oldDataArray;
    }

    void update()
    {
        for (int shiftRegisterIndex = this->_shiftRegisterCount - 1; shiftRegisterIndex >= 0; shiftRegisterIndex--)
        {
            this->_shiftRegister->shiftOut(this->_data[this->_time + shiftRegisterIndex * this->_resolution]);
        }
        this->_shiftRegister->update();

        if (this->_rowIndex++ >= this->_rowCount)
        {
            this->_rowIndex = 0;
            this->_time = (this->_time + 1) % this->_resolution;
        }
    }

    static MatrixShiftRegister *Singleton; // used inside the ISR
    ESP8266Timer Timer;
    const long UpdateCycleCountInterval = 20;
    const size_t DataArrayLength = this->_resolution * this->_shiftRegisterCount * this->_rowCount;

private:
    FastEsp8266ShiftRegister *_shiftRegister;
    uint8_t *_data;

    const uint8_t _resolution = 255;
    const uint8_t _shiftRegisterCount = 4;
    const uint8_t _rowCount = 8;
    volatile uint8_t _time = 0;
    volatile uint8_t _rowIndex = 0;
};

// One static reference to the MatrixShiftRegister that was lastly created. Used for access through timer interrupts.
MatrixShiftRegister *MatrixShiftRegister::Singleton = NULL;

#endif
