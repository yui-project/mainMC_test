#include "Mcp3204.h"
#include "Arduino.h"
#include "Decoder.h"
#include <SPI.h>

// TODO ピン番号の確認
#define cs_ADC 10

Decoder decoder;

int Mcp3204(int CH)
{
    // NOTE ここ消してよしstatic char f;
    int d1;
    int d2;

    // ADCから指定チャンネルのデータを読み出す
    decoder.write(3);
    d1 = SPI5.transfer(0x06 | (CH >> 2));
    d1 = SPI5.transfer(CH << 6);
    d2 = SPI5.transfer(0x00);
    decoder.write(7);

    return (d1 & 0x0F) * 256 + d2;
}

// Mcp3204(cs,CH)：MCP3204からアナログ値を読み取る処理
//  cs：SPIのCSピン番号を指定する
//  CH：読み取るチャンネルを指定する(0-3ch)