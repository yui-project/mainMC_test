#include "Arduino.h"
#include "CommunicationWithPowerMC.h"

CommunicationWithPowerMC::CommunicationWithPowerMC()
{
    Serial2.begin(57600);
}

uint32_t CommunicationWithPowerMC::receiveTsukutoTime()
{
    // NOTE ACK1が返ってきたらこの関数を呼び出す
    digitalWrite(ltc, LOW);
    receiveTime = 0;

    receiveTime |= ((uint32_t)Serial2.read()) << 24;
    receiveTime |= ((uint32_t)Serial2.read()) << 16;
    receiveTime |= ((uint32_t)Serial2.read()) << 8;
    receiveTime |= ((uint32_t)Serial2.read());


    Serial.print("GET:");
    Serial.println(receiveTime);

    digitalWrite(ltc, HIGH);
    delay(1);
    Serial2.write(ACK);
    Serial2.flush();

    return receiveTime;
}

bool CommunicationWithPowerMC::sendTsukutoTime(uint32_t TsukutoTime)
{
    // NOTE ACK1が返ってきたらこの関数を呼び出す
    // FIXME 多分bit数間違えてる　TSUKUTO時刻周りの仕様固まったら修正

    TsukutoTime = 45;

    digitalWrite(ltc, HIGH);
    //delay(1);

    Serial.print("SEND1:");
    Serial.println((TsukutoTime >> 24) & 0xFF);
    Serial2.write((TsukutoTime >> 24) & 0xFF);
    Serial2.flush();

    Serial.print("SEND2:");
    Serial.println((TsukutoTime >> 16) & 0xFF);
    Serial2.write((TsukutoTime >> 16) & 0xFF);
    Serial2.flush();

    Serial.print("SEND3:");
    Serial.println((TsukutoTime >> 8) & 0xFF);
    Serial2.write((TsukutoTime >> 8) & 0xFF);
    Serial2.flush();

    Serial.print("SEND4:");
    Serial.println((TsukutoTime) & 0xFF);
    Serial2.write((TsukutoTime) & 0xFF);
    Serial2.flush();

    Serial.println("SENT!!!!");

    delay(1);

    digitalWrite(ltc, LOW);
    if (confirmationAck() == true)
    {
        digitalWrite(ltc, HIGH);
        return true;
    }
    else
    {
        digitalWrite(ltc, HIGH);
        return false;
    }
}

bool CommunicationWithPowerMC::confirmationAck()
{
    int counter = 0;
    // TODO 脱出用の条件を作る必要あり
    while (Serial2.available() > 0)
    {
        digitalWrite(ltc, LOW);
        Serial.println("WAITING!!!!!");
        uint8_t ackOrNck = Serial2.read();
        if (ackOrNck == ACK)
        {
            return true;
        }
        else
        {
            // return false;
        }

        counter++;

        if (counter > 100)
        {
            Serial.println("STOP WAITING!!!");
            return false;
        }

        delay(10);
    }
}
