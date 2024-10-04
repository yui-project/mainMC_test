#include "SpiFram.h"

SpiFram spiFram;

void setup()
{
    Serial.begin(115200);
    spiFram.begin();
}

void loop()
{
    Serial.println("RESET");
    delay(1000);
    spiFram.reset(0x00);
    Serial.println("WRITE");
    for (int i = 0; i < 10; i++)
    {
        spiFram.write(i, i * i);
    }
    Serial.println("READ");
    for (int i = 0; i < 10; i++)
    {
        Serial.println(spiFram.read(i));
    }
    Serial.println("READ END");
    delay(1000);
}