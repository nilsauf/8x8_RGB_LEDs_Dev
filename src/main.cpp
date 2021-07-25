#include <Arduino.h>
#include <RgbMatrix.hpp>

#define ROW_COUNT 8
#define COLUMN_COUNT 8
#define MAX_BRIGHTNESS 255

RgbMatrix matrix(ROW_COUNT, COLUMN_COUNT);

void SetupMatrix()
{
  for (size_t rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++)
  {
    RgbMatrixLedRow *rgbRowAtIndex = new RgbMatrixLedRow(rowIndex);
    for (size_t ledIndex = 0; ledIndex < COLUMN_COUNT; ledIndex++)
    {
      RgbMatrixLed *rgbLedAtIndex = new RgbMatrixLed(
          ledIndex,
          0 + 3 * ledIndex,
          1 + 3 * ledIndex,
          2 + 3 * ledIndex,
          MAX_BRIGHTNESS);
      rgbRowAtIndex->WithRgbLedAt(rgbLedAtIndex, ledIndex);
    }

    matrix.WithRowAt(rgbRowAtIndex, rowIndex);
  }
}

void setup()
{
  // put your setup code here, to run once:

  SetupMatrix();
}

void loop()
{
  // put your main code here, to run repeatedly:
}