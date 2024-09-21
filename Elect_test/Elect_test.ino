#include "Arduino.h"
#include "Elect.h"
#include <SPI.h>

Elect El;

void setup()
{
    Serial.begin(115200);
    SPI5.begin();
    SPI5.setClockDivider(SPI_CLOCK_DIV128);
    SPI5.setDataMode(SPI_MODE0);
    SPI5.setBitOrder(MSBFIRST);

    pinMode(cs1, OUTPUT);
}


void loop()
{
    //NOTE:以下に試験時に欲しい処理を書く
}