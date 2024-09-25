#include "IoExpander.h"
#include "Arduino.h"
#include <SPI.h>
IoExpander::IoExpander()
{
}

void IoExpander::init()
{
    decoder.init();
   // TODO 初期設定ではデコーダは7番をLOWにしている
    decoder.write(7);
    SPI5.begin();
    SPI5.setBitOrder(MSBFIRST);
    SPI5.setDataMode(SPI_MODE0);
    SPI5.setClockDivider(SPI_CLOCK_DIV128);

    // MCP23S08の初期設定
    // 全てのピンを出力に設定
    write(MCP23S08_IODIR, 0x00);
    // 全てのピンをLOWに設定
    write(MCP23S08_GPIO, gpioState);
}

void IoExpander::setPin(int pin, int value)
{
    if (value == HIGH)
    {
        gpioState |= (1 << pin); // 指定ピンをHIGHに設定
    }
    else
    {
        gpioState &= ~(1 << pin); // 指定ピンをLOWに設定
    }
    write(MCP23S08_GPIO, gpioState);
}

void IoExpander::write(byte reg, byte data)
{
    decoder.write(6);
    SPI5.transfer(0x40); // MCP23S08のアドレス（デフォルトは0x40）
    SPI5.transfer(reg);
    SPI5.transfer(data);
    decoder.write(7);
}

byte IoExpander::read(byte reg)
{
    decoder.write(6);
    SPI5.transfer(0x41); // MCP23S08のアドレス（読み取りは0x41）
    SPI5.transfer(reg);
    byte data = SPI5.transfer(0x00);
    decoder.write(7);
    return data;
}