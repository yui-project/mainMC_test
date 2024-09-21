#include "AntennaDeployment.h"
#include "IoExpander.h"
#include "SPI.h"

AntennaDeployment antenna;
IoExpander ex;

void setup() {
  Serial.begin(9600);
  SPI5.begin();
  SPI5.setBitOrder(MSBFIRST);
  SPI5.setDataMode(SPI_MODE0);
  SPI5.setClockDivider(SPI_CLOCK_DIV128);
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

  ex.setPin(6,HIGH);
  delay(3000);
  ex.setPin(6,LOW);
  delay(3000);
  
}
