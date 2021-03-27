#ifndef MATRIX_LED
#define MATRIX_LED

#include <Arduino.h>

class MatrixLed
{
public:
    MatrixLed(const uint8_t cathodeIndex, const uint8_t anodeIndex, const uint8_t maxBrightness)
    {
        this->_anodeIndex = anodeIndex;
        this->_cathodeIndex = cathodeIndex;
        this->_maxBrightness = maxBrightness;
    }

    uint8_t GetPwmState()
    {
        return this->_State;
    }

    void SetPwmState(uint8_t newPwmState)
    {
        if (newPwmState > this->_maxBrightness)
        {
            newPwmState = this->_maxBrightness;
        }
        this->_State = newPwmState;
    }

    bool GetState()
    {
        return this->_State != 0;
    }

    void SetOn()
    {
        this->_State = this->_maxBrightness;
    }

    void SetOff()
    {
        this->_State = 0;
    }

    uint8_t GetAnodeIndex()
    {
        return this->_anodeIndex;
    }

    uint8_t GetCathodeIndex()
    {
        return this->_cathodeIndex;
    }

protected:
    uint8_t _cathodeIndex;
    uint8_t _anodeIndex;
    uint8_t _maxBrightness;
    volatile uint8_t _State = 0;
};

#endif