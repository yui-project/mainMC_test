#include <Arduino.h>
#include <SPI.h>
#include "BatteryCapa.h"

BatteryCapa batteryCapa;


void setup()
{
    Serial.begin(115200);
    SPI5.begin();
    SPI5.setClockDivider(SPI_CLOCK_DIV2);
    SPI5.setDataMode(SPI_MODE0);
    SPI5.setBitOrder(MSBFIRST);
}

void loop()
{
    Serial.print("Battery Capacity: ");
    Serial.println(batteryCapa.measure());
    delay(1000);
}