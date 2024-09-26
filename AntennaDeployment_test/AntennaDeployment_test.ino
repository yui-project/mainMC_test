#include "AntennaDeployment.h"
#include "IoExpander.h"

AntennaDeployment antenna;
IoExpander ex;

void setup()
{
  ex.init();
  Serial.begin(115200);
}

void loop()
{
  /*if(antenna.isOpen() == true){
      Serial.println("CLOSE!!!");
  }
  else{
    Serial.println("OPEN!!!");
  }*/
  Serial.println("START!!!");
  antenna.startUp();
  Serial.println("END!!!");
  delay(1000);
  //Serial.print("point: ");
  //Serial.println(ex.read(6));
  /*ex.setPin(6, HIGH);
  delay(3000);
  ex.setPin(6, LOW);
  delay(3000);*/
}
