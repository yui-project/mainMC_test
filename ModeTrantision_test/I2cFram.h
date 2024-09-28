#pragma once
#include "Arduino.h"

class I2cFram
{
private:
//NOTE:岸田のコードだとここはbyteになっていたけどエラー吐いたのでintに修正
    int deviceaddress;

public:
    I2cFram();
    void begin();
    void reset(byte address1, byte address2, int reset_data);
    void write(byte addrress, unsigned int eeaddress, byte data);
    byte read(byte addrress, unsigned int eeaddress);
};