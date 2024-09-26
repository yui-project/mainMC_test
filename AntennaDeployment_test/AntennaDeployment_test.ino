#include "AntennaDeployment.h"
#include "IoExpander.h"

AntennaDeployment antenna;
IoExpander ex;

void setup() {
  ex.init();
}

void loop() {
  /*if(antenna.isOpen() == true){
      Serial.println("CLOSE!!!");
  }
  else{
    Serial.println("OPEN!!!");
  }*/
  /*Serial.println("START!!!");
  antenna.startUp();
  Serial.println("END!!!");
  delay(1000);*/
  Serial.println("OPEN!!!");
  ex.setPin(6,HIGH);
}
