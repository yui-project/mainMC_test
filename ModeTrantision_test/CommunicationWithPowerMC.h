#pragma once
#include "Arduino.h"
class CommunicationWithPowerMC
{
private:
    uint8_t ltc = 26; // TODO トランシーバICのピン番号の確認
#define ACK 0x06
    uint32_t receiveTime = 0;

public:
    CommunicationWithPowerMC();
    bool confirmationAck();
    uint32_t receiveTsukutoTime();
    bool sendTsukutoTime(uint32_t TsukutoTime);
};