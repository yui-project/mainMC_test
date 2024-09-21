#include "AntennaDeployment.h"
#include "Arduino.h"


AntennaDeployment::AntennaDeployment() {
}

void AntennaDeployment::startUp() {
  while (isOpen() == false) {
    ioExpander.setPin(AntennaDeploymentPin, HIGH);
    counter++;
    if (counter > 30000) {  //NOTE 無限ループ対策　脱出の基準はもっと大きくしても良い
      ioExpander.setPin(AntennaDeploymentPin, LOW);
      counter = 0;
      return;
    }
    delay(1);
  }
  counter = 0;
  ioExpander.setPin(AntennaDeploymentPin, LOW);
}


bool AntennaDeployment::isOpen() {
  //NOTE:ハードの関係で電源マイコンと逆で閉じていたらtrue、開いてたらfalseを出す
  //Serial.println(ioExpander.read(AntennaDeploymentConfirmPin));
  if (ioExpander.read(AntennaDeploymentConfirmPin) == 0) {
    return false;
  } else {
    return true;
  }
}