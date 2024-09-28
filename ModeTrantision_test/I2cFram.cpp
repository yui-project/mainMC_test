#include "I2cFram.h"
#include "Wire.h"

I2cFram::I2cFram()
{
}

void I2cFram::begin()
{
    Wire.begin();
    Wire.setClock(400000);
}

void I2cFram::reset(byte address1, byte address2, int reset_data)
{
    deviceaddress = address1;
    for (unsigned int i = 0; i < pow(2, 16) - 1; i++)
    {
        Wire.beginTransmission(deviceaddress);
        Wire.write((int)(i >> 8));   // MSB
        Wire.write((int)(i & 0xFF)); // LSB
        Wire.write(reset_data);
        Wire.endTransmission();
    }
    deviceaddress = address2;
    for (unsigned int i = 0; i < pow(2, 16) - 1; i++)
    {
        Wire.beginTransmission(deviceaddress);
        Wire.write((int)(i >> 8));   // MSB
        Wire.write((int)(i & 0xFF)); // LSB
        Wire.write(reset_data);
        Wire.endTransmission();
    }
}

void I2cFram::write(byte address, unsigned int eeaddress, byte data)
{
    deviceaddress = address;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(data);
    Wire.endTransmission();
}

byte I2cFram::read(byte address, unsigned int eeaddress)
{
    deviceaddress = (int)address;
    byte rdata = 0x00;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();

    Wire.requestFrom(deviceaddress, 1);
    if (Wire.available())
        rdata = Wire.read();
    return rdata;
}