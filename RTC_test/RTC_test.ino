#include "RealTimeClock.h"

RealTimeClock RTC;
void setup()
{
    Serial.begin(115200);
    RTC.init();
}

void loop(){
    Serial.print("NOW TIME");
    Serial.println(RTC.get());
    delay(1000);
}