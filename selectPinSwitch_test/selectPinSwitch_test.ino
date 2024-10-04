#include "IoExpander.h"
#include "Arduino.h"

#define MMC_T_HEATER 2
#define PMC_RESET 3
#define MISSION_MODULE 6

uint8_t switch_num = 0;

IoExpander ex;

void setup()
{
    Serial.begin(115200);
    ex.init();
}

void loop()
{
    if (Serial.available() > 0)
    {
        int receivedValue = Serial.read() - '0';
        if (receivedValue >= 1 && receivedValue <= 6)
        {

            if (receivedValue == 2)
            {
                Serial.println("SWITCH:MMC_T_HEATER");
                switch_num = MMC_T_HEATER;
            }
            else if (receivedValue == 3)
            {
                Serial.println("SWITCH:PMC_RESET");
                switch_num = PMC_RESET;
            }
            else if (receivedValue == 6)
            {
                Serial.println("SWITCH:MISSION_MODULE");
                switch_num = MISSION_MODULE;
            }
        }
        else if (receivedValue == 10)
        {
            Serial.println("SWITCH:OFF");
            ex.setPin(switch_num,LOW);
        }
        else if (receivedValue == 11)
        {
            Serial.println("SWITCH:ON");
            ex.setPin(switch_num, HIGH);
        }
        else
        {
            Serial.println("無効な入力です");
            switch_num = 0;
        }
    }
    delay(1000);
}