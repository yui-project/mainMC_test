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
    pinMode(20, OUTPUT);
    pinMode(21, OUTPUT);
}


void loop()
{
    digitalWrite(20, HIGH);
    digitalWrite(21, HIGH);
    Serial.print("BatteryVolt:");
    Serial.println(El.getElectVolt(3));
    Serial.print("GETELECTLORAVOLT:");
    Serial.println(El.getElectVolt(1));
    Serial.print("GETELECTLORACURRENT:");
    Serial.println(El.getElectCurrent(1));
    Serial.print("GETELECTBACKUPVOLT:");
    Serial.println(El.getElectVolt(2));
    Serial.print("GETELECTBACKUPCURRENT:");
    Serial.println(El.getElectCurrent(2));
    Serial.println("----------------------------------");
    delay(1000);
}