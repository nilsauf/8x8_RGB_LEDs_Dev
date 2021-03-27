#ifndef RGB_MATRIX_LED
#define RGB_MATRIX_LED

#include <Arduino.h>
#include <MatrixLed.hpp>
#include <string>

enum ERgbLedColor
{
    Red,
    Green,
    Blue
};

class RgbMatrixLed
{
public:
    RgbMatrixLed(const uint8_t cathodeIndex, const uint8_t redIndex, const uint8_t greenIndex, const uint8_t blueIndex, const uint8_t maxBrightness)
        : RgbMatrixLed(cathodeIndex,
                       new MatrixLed(cathodeIndex, redIndex, maxBrightness),
                       new MatrixLed(cathodeIndex, greenIndex, maxBrightness),
                       new MatrixLed(cathodeIndex, blueIndex, maxBrightness))
    {
    }

    RgbMatrixLed(const uint8_t cathodeIndex, MatrixLed *red, MatrixLed *green, MatrixLed *blue)
    {
        this->_cathodeIndex = cathodeIndex;

        this->_red = red;
        this->_green = green;
        this->_blue = blue;
    }

    uint8_t GetCathodeIndex()
    {
        return this->_cathodeIndex;
    }

    uint8_t GetAnodeColorIndex(ERgbLedColor color)
    {
        switch (color)
        {
        case Red:
            return this->_red->GetAnodeIndex();
        case Green:
            return this->_green->GetAnodeIndex();
        case Blue:
            return this->_blue->GetAnodeIndex();
        default:
            return 255;
        }
    }

    void SetPwmStates(uint8_t *pwmStates)
    {
        this->SetPwmStates(pwmStates[Red], pwmStates[Green], pwmStates[Blue]);
    }

    void SetPwmStates(uint8_t redPwmState, uint8_t greenPwmState, uint8_t bluePwmState)
    {
        this->_red->SetPwmState(redPwmState);
        this->_green->SetPwmState(greenPwmState);
        this->_blue->SetPwmState(bluePwmState);
    }

    uint8_t *GetPwmStates()
    {
        uint8_t *retArray = (uint8_t *)malloc(sizeof(uint8_t) * 3);
        retArray[0] = this->_red->GetPwmState();
        retArray[1] = this->_green->GetPwmState();
        retArray[2] = this->_blue->GetPwmState();
        return retArray;
    }

    uint8_t GetColorPwmState(ERgbLedColor color)
    {
        switch (color)
        {
        case Red:
            return this->_red->GetPwmState();
        case Green:
            return this->_green->GetPwmState();
        case Blue:
            return this->_blue->GetPwmState();
        default:
            return 0;
        }
    }

    void SetColorPwmState(ERgbLedColor color, uint8_t newPwmState)
    {
        switch (color)
        {
        case Red:
            this->_red->SetPwmState(newPwmState);
            break;
        case Green:
            this->_green->SetPwmState(newPwmState);
            break;
        case Blue:
            this->_blue->SetPwmState(newPwmState);
            break;
        }
    }

    MatrixLed *GetColorLed(ERgbLedColor color)
    {
        switch (color)
        {
        case Red:
            return this->_red;
        case Green:
            return this->_green;
        case Blue:
            return this->_blue;
        }
    }

private:
    uint8_t _cathodeIndex;

    MatrixLed *_red;
    MatrixLed *_green;
    MatrixLed *_blue;
};

#endif