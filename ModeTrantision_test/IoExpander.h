#pragma once
#include "Arduino.h"
#include "Decoder.h"
class IoExpander
{
private:
    Decoder decoder;

// MCP23S08のレジスタアドレス
#define MCP23S08_IODIR 0x00 // I/Oディレクションレジスタ
#define MCP23S08_GPIO 0x09  // GPIOレジスタ
#define MCP23S08_OLAT 0x0A  // 出力ラッチレジスタ

    // 現在のGPIO状態を保持する変数
    byte gpioState = 0x00;

public:
    IoExpander();
    void init();
    void setPin(int pin, int value);
    void write(byte reg, byte data);
    byte read(byte reg);
};